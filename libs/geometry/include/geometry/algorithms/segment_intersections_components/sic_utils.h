#pragma once

#include <set>
#include "geometry/model/segment_2.h"
#include "geometry/model/DCEL.h"


namespace geometry::segment_intersections_components
{
	typedef DCEL::hedge hedge;
	typedef std::vector<segment_2> segment_2_set;

	DCEL brute_dcel(const segment_2_set& S);

	bool up_edge(hedge* h);
}
