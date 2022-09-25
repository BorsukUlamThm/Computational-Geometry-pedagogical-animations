#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/DCEL.h"


namespace geometry
{
	DCEL convex_hull(const std::vector<point_2>& P);
}