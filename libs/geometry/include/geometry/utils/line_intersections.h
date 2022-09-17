#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"


namespace geometry
{
	bool segment_intersect(const segment_2& s1,
						   const segment_2& s2);
	point_2 line_intersection(const segment_2& s1,
							  const segment_2& s2);
	real x_intersection(const segment_2& s,
						const real& y);
}