#include "geometry/algorithms/segment_intersections.h"
#include "geometry/algorithms/segment_intersections_components/sic_utils.h"
#include "geometry/algorithms/segment_intersections_components/sic_tree.h"
#include "geometry/algorithms/segment_intersections_components/sic_events.h"
#include "geometry/utils/line_intersections.h"
#include <map>


namespace geometry
{
	namespace sic = segment_intersections_components;

	DCEL segment_intersections(const std::vector<segment_2>& S)
	{
		DCEL D = sic::brute_dcel(S);
		sic::tree T;
		//		T.plot_segments(S);
		sic::queue Q(D, T);

		Q.handle_events();

		return D;
	}

	bool test_interior_intersection(std::map<DCEL::hedge*, unsigned>& map,
									DCEL::hedge* h1,
									DCEL::hedge* h2)
	{
		if (h1 == nullptr || h2 == nullptr)
		{ return false; }

		if (hedges_intersect_interior(h1, h2))
		{
			unsigned i = map[h1];
			unsigned j = map[h2];

			std::cerr << "Invalid DCEL " << i << "-th half edge and "
					  << j << "-th half edge intersect"
					  << " in their interior"
					  << std::endl;
			return true;
		}

		return false;
	}

	std::vector<DCEL::hedge*> make_up_events(const DCEL& D)
	{
		std::vector<DCEL::hedge*> events;

		for (auto& h : D.half_edges)
		{
			if (sic::up_edge(h))
			{ events.push_back(h); }
		}

		std::sort(events.begin(), events.end(), sic::hedge_below_hedge);

		return events;
	}

	std::vector<DCEL::hedge*> make_down_events(const DCEL& D)
	{
		std::vector<DCEL::hedge*> events;

		for (auto& h : D.half_edges)
		{
			if (!sic::up_edge(h))
			{ events.push_back(h); }
		}

		std::sort(events.begin(), events.end(), sic::hedge_below_hedge);

		return events;
	}

	bool handle_up_edge(DCEL::hedge* h,
						std::map<DCEL::hedge*, unsigned>& map,
						sic::tree& T)
	{
		T.set_event_p({h->origin->x, h->origin->y});

		DCEL::hedge* t = h->twin;
		auto* l_node = T.find_left_neighbour(t);
		DCEL::hedge* l = (l_node ? l_node->root : nullptr);
		auto* r_node = T.find_right_neighbour(t);
		DCEL::hedge* r = (r_node ? r_node->root : nullptr);

		if (test_interior_intersection(map, t, l))
		{ return true; }

		if (test_interior_intersection(map, t, r))
		{ return true; }

		T.set_comparison_just_above();
		T.remove(t);

		return false;
	}

	bool handle_down_edge(DCEL::hedge* h,
						  std::map<DCEL::hedge*, unsigned>& map,
						  sic::tree& T)
	{
		T.set_event_p({h->origin->x, h->origin->y});

		auto* l_node = T.find_left_neighbour(h);
		DCEL::hedge* l = (l_node ? l_node->root : nullptr);
		auto* r_node = T.find_right_neighbour(h);
		DCEL::hedge* r = (r_node ? r_node->root : nullptr);

		if (test_interior_intersection(map, l, r))
		{ return true; }

		T.set_comparison_just_below();
		T.insert(h);

		return false;
	}

	bool edge_intersections_test(const DCEL& D)
	{
		std::map<DCEL::hedge*, unsigned> map = sic::make_index_map(D);

		std::vector<DCEL::hedge*> up_events = make_up_events(D);
		std::vector<DCEL::hedge*> down_events = make_down_events(D);

		sic::tree T;

		while (up_events.size() + down_events.size() > 0)
		{
			DCEL::hedge* u = (up_events.empty() ? nullptr :
							  up_events[up_events.size() - 1]);
			DCEL::hedge* d = (down_events.empty() ? nullptr :
							  down_events[down_events.size() - 1]);

			if (u == nullptr)
			{
				if (handle_down_edge(d, map, T))
				{ return true; }
				down_events.pop_back();

//				std::cout << T.depth() << std::endl;
				continue;
			}
			if (d == nullptr)
			{
				if (handle_up_edge(u, map, T))
				{ return true; }
				up_events.pop_back();

//				std::cout << T.depth() << std::endl;
				continue;
			}

			if (sic::hedge_below_hedge(d, u))
			{
				if (handle_up_edge(u, map, T))
				{ return true; }
				up_events.pop_back();
			}
			else
			{
				if (handle_down_edge(d, map, T))
				{ return true; }
				down_events.pop_back();
			}

//			std::cout << T.depth() << std::endl;
		}

		return false;
	}
}