#pragma once

#include <map>
#include "geometry/model/segment_2.h"
#include "geometry/model/DCEL.h"


namespace geometry::segment_intersections_components
{
	typedef DCEL::hedge hedge;
	typedef DCEL::face face;
	typedef std::vector<segment_2> segment_2_set;

	DCEL brute_dcel(const segment_2_set& S);

	bool up_edge(hedge* h);

	bool hedge_below_hedge(hedge* h1,
						   hedge* h2);

	std::vector<DCEL::hedge*> make_up_events(const DCEL& D);

	std::vector<DCEL::hedge*> make_down_events(const DCEL& D);

	std::map<DCEL::hedge*, unsigned> make_index_map(const DCEL& D);
}
