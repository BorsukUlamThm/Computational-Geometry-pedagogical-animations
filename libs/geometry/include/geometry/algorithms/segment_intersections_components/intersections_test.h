#pragma once

#include "geometry/model/DCEL.h"
#include "geometry/algorithms/segment_intersections_components/sic_tree.h"
#include <map>


namespace geometry::segment_intersections_components
{
	bool test_interior_intersection(std::map<DCEL::hedge*, unsigned>& map,
									DCEL::hedge* h1,
									DCEL::hedge* h2);

	std::vector<DCEL::hedge*> make_up_events(const DCEL& D);

	std::vector<DCEL::hedge*> make_down_events(const DCEL& D);

	bool intersection_test_handle_up_edge(DCEL::hedge* h,
										  std::map<DCEL::hedge*, unsigned>& map,
										  tree& T);

	bool intersection_test_handle_down_edge(DCEL::hedge* h,
											std::map<DCEL::hedge*, unsigned>& map,
											tree& T);
}