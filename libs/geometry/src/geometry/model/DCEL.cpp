#include "geometry/model/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/line_intersections.h"
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

	DCEL::vertex::vertex(const real& x,
						 const real& y,
						 hedge* inc_edge) :
			x(x),
			y(y),
			inc_edge(inc_edge)
	{}

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

	DCEL::face::face(std::vector<hedge*> inner_comp,
					 hedge* outer_comp) :
			inner_comp(std::move(inner_comp)),
			outer_comp(outer_comp)
	{}

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

		return valid;
	}

	bool DCEL::overlap_check()
	{
		bool valid = true;

		for (unsigned i = 0; i < half_edges.size(); ++i)
		{
			for (unsigned j = i + 1; j < half_edges.size(); ++j)
			{
				if (half_edges[i]->twin == half_edges[j])
				{ continue; }

				if (hedges_overlap(half_edges[i], half_edges[j]))
				{
					std::cerr << "Invalid DCEL " << i << "-th half edge and"
							  << j << "-th half edge overlap" << std::endl;
					valid = false;
				}
			}
		}

		return valid;
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

		if ((mask & OVERLAP_CHECK) == OVERLAP_CHECK)
		{ valid = valid && overlap_check(); }

		return valid;
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
			}
		}
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