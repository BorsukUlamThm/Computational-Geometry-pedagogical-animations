#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include "geometry/model/DCEL.h"


namespace geometry
{
	bool segment_intersect(const segment_2& s1,
						   const segment_2& s2);
	bool segment_overlap(const segment_2& s1,
						 const segment_2& s2);
	point_2 line_intersection(const segment_2& s1,
							  const segment_2& s2);
	real x_intersection(const segment_2& s,
						const real& y);

	bool hedges_intersect(DCEL::hedge* h1,
						  DCEL::hedge* h2);
	bool hedges_overlap(DCEL::hedge* h1,
						DCEL::hedge* h2);
	point_2 line_intersection(DCEL::hedge* h1,
							  DCEL::hedge* h2);
	real x_intersection(DCEL::hedge* h,
						const real& y);
}