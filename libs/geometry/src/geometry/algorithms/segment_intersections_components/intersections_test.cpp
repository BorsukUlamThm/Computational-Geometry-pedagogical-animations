#include "geometry/algorithms/segment_intersections_components/intersections_test.h"
#include "geometry/algorithms/segment_intersections_components/sic_utils.h"
#include "geometry/algorithms/segment_intersections_components/sic_tree.h"
#include "geometry/utils/line_intersections.h"

namespace geometry::segment_intersections_components
{
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

	bool intersection_test_handle_up_edge(DCEL::hedge* h,
										  std::map<DCEL::hedge*, unsigned>& map,
										  tree& T)
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

	bool intersection_test_handle_down_edge(DCEL::hedge* h,
											std::map<DCEL::hedge*, unsigned>& map,
											tree& T)
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
}