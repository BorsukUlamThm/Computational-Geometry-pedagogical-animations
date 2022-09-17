#pragma once

#include "geometry/model/point.h"
#include "geometry/model/segment.h"


namespace geometry
{
	bool segment_intersect(const segment& s1,
						   const segment& s2);
	point line_intersection(const segment& s1,
							const segment& s2);
	real x_intersection(const segment& s,
						const real& y);
}