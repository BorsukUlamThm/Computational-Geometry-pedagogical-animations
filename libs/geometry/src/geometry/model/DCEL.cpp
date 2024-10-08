#include "geometry/model/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/algorithms/segment_intersections.h"
#include "geometry/utils/point_comparisons.h"
#include <iostream>
#include <map>


namespace geometry
{
	DCEL::~DCEL()
	{
		for (auto& ptr : vertices)
		{ delete ptr; }

		for (auto& ptr : half_edges)
		{ delete ptr; }

		for (auto& ptr : faces)
		{ delete ptr; }
	}

	void DCEL::component::mark(mark_t m)
	{ marks |= m; }

	void DCEL::component::unmark(mark_t m)
	{ marks &= ~m; }

	bool DCEL::component::is_marked(mark_t m) const
	{ return (marks & m) == m; }

	DCEL::vertex::vertex(const number& x,
						 const number& y,
						 hedge* inc_edge) :
			x(x),
			y(y),
			inc_edge(inc_edge)
	{}

	unsigned DCEL::vertex::degree() const
	{
		unsigned d = 0;
		hedge* h = inc_edge;

		do
		{
			d++;
			h = h->prev->twin;
		}
		while (h != inc_edge);

		return d;
	}

	void DCEL::vertex::add_to_figure(gr::Figure& fig,
									 gr::Color col)
	{
		gr::Coordinate vx(x);
		gr::Coordinate vy(y);

		fig.add_point(vx, vy, col);
	}

	DCEL::hedge::hedge(vertex* origin,
					   hedge* prev,
					   hedge* next,
					   hedge* twin,
					   face* inc_face) :
			origin(origin),
			prev(prev),
			next(next),
			twin(twin),
			inc_face(inc_face)
	{}

	void DCEL::hedge::add_to_figure(gr::Figure& fig,
									gr::Color col)
	{
		gr::Coordinate ogn_x(origin->x);
		gr::Coordinate ogn_y(origin->y);
		gr::Coordinate dst_x(twin->origin->x);
		gr::Coordinate dst_y(twin->origin->y);
		fig.add_half_edge(ogn_x, ogn_y, dst_x, dst_y, col);
	}

	DCEL::face::face(std::vector<hedge*> inner_comp,
					 hedge* outer_comp) :
			inner_comp(std::move(inner_comp)),
			outer_comp(outer_comp)
	{}

	void DCEL::face::add_to_figure(gr::Figure& fig,
								   gr::Color col)
	{
		if (outer_comp)
		{
			hedge* it = outer_comp;
			do
			{
				it->add_to_figure(fig, col);
				it = it->next;
			}
			while (it != outer_comp);
		}

		for (auto& h : inner_comp)
		{
			hedge* it = h;
			do
			{
				it->add_to_figure(fig, col);
				it = it->next;
			}
			while (it != h);
		}
	}

	bool DCEL::vertices_check()
	{
		bool valid = true;

		for (unsigned i = 0; i < vertices.size(); ++i)
		{
			hedge* h = vertices[i]->inc_edge;
			do
			{
				if (h->origin != vertices[i])
				{
					std::cerr << "Invalid DCEL " << i << "-th vertex incident"
							  << " edges are note all valid" << std::endl;
					valid = false;
				}
				h = h->prev->twin;
			}
			while (h != vertices[i]->inc_edge);
		}

		return valid;
	}

	bool DCEL::hedges_check()
	{
		bool valid = true;

		for (unsigned i = 0; i < half_edges.size(); ++i)
		{
			if (half_edges[i]->prev->next != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge prev is"
						  << " invalid" << std::endl;
				valid = false;
			}
			if (half_edges[i]->next->prev != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge next is"
						  << " invalid" << std::endl;
				valid = false;
			}
			if (half_edges[i]->twin->twin != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge twin is"
						  << " invalid" << std::endl;
				valid = false;
			}
		}

		return valid;
	}

	bool DCEL::faces_check()
	{
		bool valid = true;
		unsigned nb_unbounded_faces = 0;

		for (unsigned i = 0; i < faces.size(); ++i)
		{
			if (faces[i]->outer_comp)
			{
				hedge* h = faces[i]->outer_comp;
				do
				{
					if (h->inc_face != faces[i])
					{
						std::cerr << "Invalid DCEL " << i << "-th face"
								  << " outer_comp boundary is invalid"
								  << std::endl;
						valid = false;
					}
					h = h->next;
				}
				while (h != faces[i]->outer_comp);
			}
			else
			{ nb_unbounded_faces++; }

			for (hedge* it : faces[i]->inner_comp)
			{
				hedge* h = it;
				do
				{
					if (h->inc_face != faces[i])
					{
						std::cerr << "Invalid DCEL " << i << "-th face"
								  << " inner_comp boundary is invalid"
								  << std::endl;
						valid = false;
					}
					h = h->next;
				}
				while (h != it);
			}
		}

		if (nb_unbounded_faces != 1)
		{
			std::cerr << "Invalid DCEL found " << nb_unbounded_faces
					  << " unbounded faces instead of only one"
					  << std::endl;
			valid = false;
		}

		return valid;
	}

	bool DCEL::intersection_check() const
	{
		return !edge_intersections_test(*this);
	}

	bool DCEL::is_valid(unsigned mask)
	{
		bool valid = true;

		if ((mask & VERTICES_CHECK) == VERTICES_CHECK)
		{ valid = valid && vertices_check(); }

		if ((mask & HEDGES_CHECK) == HEDGES_CHECK)
		{ valid = valid && hedges_check(); }

		if ((mask & FACES_CHECK) == FACES_CHECK)
		{ valid = valid && faces_check(); }

		if ((mask & INTERSECTION_CHECK) == INTERSECTION_CHECK)
		{ valid = valid && intersection_check(); }

		return valid;
	}

	DCEL::hedge* left_neighbour(DCEL::vertex* ogn,
								DCEL::vertex* dst,
								DCEL::hedge* left_inc)
	{
		DCEL::hedge* it = left_inc;
		DCEL::hedge* next = it->twin->next;

		while (point_left_line(next->twin->origin, ogn, dst) &&
			   point_right_line(next->twin->origin, it))
		{
			it = next;
			next = next->twin->next;
		}

		return it;
	}

	DCEL::hedge* right_neighbour(DCEL::vertex* ogn,
								 DCEL::vertex* dst,
								 DCEL::hedge* right_inc)
	{
		DCEL::hedge* it = right_inc;
		DCEL::hedge* next = it->prev->twin;

		while (point_right_line(next->twin->origin, ogn, dst) &&
			   point_left_line(next->twin->origin, it))
		{
			it = next;
			next = next->prev->twin;
		}

		return it;
	}

	DCEL::hedge* right_neighbour(DCEL::vertex* ogn,
								 DCEL::vertex* dst)
	{
		if (ogn->degree() == 1)
		{
			return ogn->inc_edge;
		}

		if (point_right_line(ogn->inc_edge->twin->origin, ogn, dst))
		{
			return right_neighbour(ogn, dst, ogn->inc_edge);
		}
		DCEL::hedge* left = left_neighbour(ogn, dst, ogn->inc_edge);
		return left->twin->next;
	}

	void DCEL::add_diagonal(DCEL::vertex* v1,
							DCEL::vertex* v2)
	{
		auto* h12 = new hedge();
		auto* h21 = new hedge();

		h12->origin = v1;
		h21->origin = v2;
		h12->twin = h21;
		h21->twin = h12;

		hedge* right1 = right_neighbour(v1, v2);
		hedge* right2 = right_neighbour(v2, v1);

		h12->prev = right1->prev;
		h12->next = right2;
		h21->prev = right2->prev;
		h21->next = right1;

		h12->prev->next = h12;
		h12->next->prev = h12;
		h21->prev->next = h21;
		h21->next->prev = h21;

		half_edges.push_back(h12);
		half_edges.push_back(h21);
	}

	void DCEL::clear()
	{
		for (auto& ptr : vertices)
		{ delete ptr; }

		for (auto& ptr : half_edges)
		{ delete ptr; }

		for (auto& ptr : faces)
		{ delete ptr; }

		vertices.clear();
		half_edges.clear();
		faces.clear();
	}

	DCEL::face* DCEL::get_unbounded_face() const
	{
		for (auto& f : faces)
		{
			if (f->outer_comp == nullptr)
			{
				return f;
			}
		}

		return nullptr;
	}

	DCEL::mark_t DCEL::get_new_mark()
	{
		for (unsigned i = 0; i < MAX_MARKS; ++i)
		{
			mark_t m = 1 << i;

			if ((used_marks & m) == m)
			{ continue; }

			used_marks |= m;
			return m;
		}

		std::cerr << "DCEL error : no available marks left" << std::endl;
		return 0;
	}

	void DCEL::free_mark(DCEL::mark_t m)
	{
		for (auto& v : vertices)
		{ v->unmark(m); }
		for (auto& h : half_edges)
		{ h->unmark(m); }
		for (auto& f : faces)
		{ f->unmark(m); }

		used_marks &= ~m;
	}

	void DCEL::delete_vertex(geometry::DCEL::vertex* v)
	{
		if (!v)
		{ return; }

		for (auto it = vertices.begin(); it != vertices.end(); ++it)
		{
			if (*it == v)
			{
				delete *it;
				vertices.erase(it);
				return;
			}
		}
	}

	void DCEL::delete_hedge(geometry::DCEL::hedge* h)
	{
		if (!h)
		{ return; }

		for (auto it = half_edges.begin(); it != half_edges.end(); ++it)
		{
			if (*it == h)
			{
				delete *it;
				half_edges.erase(it);
				return;
			}
		}
	}

	void DCEL::delete_face(geometry::DCEL::face* f)
	{
		if (!f)
		{ return; }

		for (auto it = faces.begin(); it != faces.end(); ++it)
		{
			if (*it == f)
			{
				delete *it;
				faces.erase(it);
				return;
			}
		}
	}

	void DCEL::add_to_figure(gr::Figure& fig)
	{
		for (auto& h : half_edges)
		{
			h->add_to_figure(fig);
		}
		for (auto& v : vertices)
		{
			v->add_to_figure(fig);
		}
	}

	gr::Animation DCEL::display_faces()
	{
		gr::Animation animation(2);
		add_to_figure(animation[0]);
		animation.make_new_frame();

		for(auto& f : faces)
		{
			f->add_to_figure(animation[1], gr::RED);
			animation.make_new_frame();
			animation[1].clear();
		}

		return animation;
	}

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& D)
	{
		std::map<void*, int> indexes;
		indexes[nullptr] = -1;

		for (int i = 0; i < D.vertices.size(); ++i)
		{ indexes[D.vertices[i]] = i; }

		for (int i = 0; i < D.half_edges.size(); ++i)
		{ indexes[D.half_edges[i]] = i; }

		for (int i = 0; i < D.faces.size(); ++i)
		{ indexes[D.faces[i]] = i; }

		for (int i = 0; i < D.vertices.size(); ++i)
		{
			os << "v" << i << " : "
			   << D.vertices[i]->x << " "
			   << D.vertices[i]->y << " "
			   << indexes[D.vertices[i]->inc_edge] << std::endl;
		}

		os << std::endl;

		for (int i = 0; i < D.half_edges.size(); ++i)
		{
			os << "h" << i << " : "
			   << indexes[D.half_edges[i]->origin] << " "
			   << indexes[D.half_edges[i]->prev] << " "
			   << indexes[D.half_edges[i]->next] << " "
			   << indexes[D.half_edges[i]->twin] << " "
			   << indexes[D.half_edges[i]->inc_face] << std::endl;
		}

		os << std::endl;

		for (int i = 0; i < D.faces.size(); ++i)
		{
			os << "f" << i << " : [";
			auto vec = D.faces[i]->inner_comp;
			for (unsigned j = 0; j < vec.size(); ++j)
			{
				os << indexes[vec[j]] << (j == vec.size() - 1 ? "" : " ");
			}
			os << "] " << indexes[D.faces[i]->outer_comp] << std::endl;
		}

		return os;
	}
}