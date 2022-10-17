#include "geometry/algorithms/segment_intersections_components/face_computation.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry::segment_intersections_components
{
	void init_marks(DCEL& D,
					DCEL::mark_t interior,
					DCEL::mark_t exterior,
					DCEL::mark_t leftmost)
	{
		for (auto& h : D.half_edges)
		{
			if (h->is_marked(interior) || h->is_marked(exterior))
			{ continue; }

			hedge* left = h;
			hedge* h1 = h;
			do
			{
				if (point_left_point(h1, left))
				{ left = h1; }

				h1 = h1->next;
			}
			while (h1 != h);

			point_2 p(left->prev->origin->x, left->prev->origin->y);
			point_2 q(left->origin->x, left->origin->y);
			point_2 r(left->next->origin->x, left->next->origin->y);
			bool exterior_face = point_right_line(p, q, r);

			if (exterior_face)
			{ left->mark(leftmost); }

			h1 = h;
			do
			{
				if (exterior_face)
				{ h1->mark(exterior); }
				else
				{ h1->mark(interior); }

				h1 = h1->next;
			}
			while (h1 != h);
		}
	}

	void face_computation_handle_up_edge(hedge* h,
										 std::vector<link>& links,
										 tree& T,
										 DCEL::mark_t leftmost)
	{
		T.set_event_p({h->origin->x, h->origin->y});

		DCEL::hedge* t = h->twin;

		if (h->is_marked(leftmost))
		{
			point_2 p(h->origin->x, h->origin->y);
			hedge* helper = T.left_neighbour(p);

			links.emplace_back(h, helper);
		}

		T.set_comparison_just_above();
		T.remove(t);
	}

	void face_computation_handle_down_edge(hedge* h,
										   std::vector<link>& links,
										   tree& T,
										   DCEL::mark_t leftmost)
	{
		T.set_event_p({h->origin->x, h->origin->y});

		if (h->is_marked(leftmost))
		{
			point_2 p(h->origin->x, h->origin->y);
			hedge* helper = T.left_neighbour(p);

			links.emplace_back(h, helper);
		}

		T.set_comparison_just_below();
		T.insert(h);
	}

	std::vector<link> make_links(DCEL& D,
								 DCEL::mark_t leftmost)
	{
		std::vector<link> links;

		std::cout << D << std::endl;

		std::vector<DCEL::hedge*> up_events = make_up_events(D);
		std::vector<DCEL::hedge*> down_events = make_down_events(D);
		tree T;

		while (up_events.size() + down_events.size() > 0)
		{
			DCEL::hedge* u = (up_events.empty() ? nullptr :
							  up_events[up_events.size() - 1]);
			DCEL::hedge* d = (down_events.empty() ? nullptr :
							  down_events[down_events.size() - 1]);

			if (u == nullptr)
			{
				face_computation_handle_down_edge(d, links, T, leftmost);
				down_events.pop_back();
				continue;
			}
			if (d == nullptr)
			{
				face_computation_handle_up_edge(u, links, T, leftmost);
				up_events.pop_back();
				continue;
			}

			if (hedge_below_hedge(d, u))
			{
				face_computation_handle_up_edge(u, links, T, leftmost);
				up_events.pop_back();
			}
			else
			{
				face_computation_handle_down_edge(d, links, T, leftmost);
				down_events.pop_back();
			}
		}

		return links;
	}

	void make_one_face(DCEL& D,
					   hedge* h,
					   DCEL::mark_t treated)
	{
		face* f = new face();
		f->outer_comp = h;
		D.faces.push_back(f);

		make_one_face(D, h, f, treated);
	}

	void make_one_face(DCEL& D,
					   hedge* h,
					   face* f,
					   DCEL::mark_t treated)
	{
		hedge* h1 = h;
		do
		{
			h1->inc_face = f;
			h1->mark(treated);
			h1 = h1->next;
		}
		while (h1 != h);
	}

	void make_faces(DCEL& D,
					std::vector<link>& links,
					DCEL::mark_t interior,
					DCEL::mark_t exterior)
	{
		face* unbounded = new face();
		D.faces.push_back(unbounded);

		DCEL::mark_t treated = D.get_new_mark();

		for (auto& h : D.half_edges)
		{
			if (h->is_marked(treated))
			{ continue; }

			if (h->is_marked(interior))
			{ make_one_face(D, h, treated); }
		}

		for (auto& l : links)
		{
			if (l.helper == nullptr)
			{
				make_one_face(D, l.leftmost, unbounded, treated);
				unbounded->inner_comp.push_back(l.leftmost);
				continue;
			}
		}

		while (!links.empty())
		{
			if (links.back().leftmost->is_marked(treated))
			{
				links.pop_back();
				continue;
			}

			unsigned i = links.size() - 1;
			while (!links[i].helper->is_marked(treated))
			{ i--; }

			make_one_face(D, links[i].leftmost,
						  links[i].helper->inc_face,
						  treated);
			links[i].helper->inc_face->inner_comp.push_back(links[i].leftmost);
		}

		D.free_mark(treated);
	}

	void compute_faces(DCEL& D)
	{
		D.faces.clear();

		DCEL::mark_t interior = D.get_new_mark();
		DCEL::mark_t exterior = D.get_new_mark();
		DCEL::mark_t leftmost = D.get_new_mark();

		init_marks(D, interior, exterior, leftmost);
		std::vector<link> links = make_links(D, leftmost);
		make_faces(D, links, interior, exterior);

		D.free_mark(interior);
		D.free_mark(exterior);
		D.free_mark(leftmost);
	}
}