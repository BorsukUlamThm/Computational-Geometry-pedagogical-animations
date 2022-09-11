#pragma once

#include <iostream>
#include "point_comparisons.h"
#include "geometry/model/Point_2.h"
#include "geometry/model/Segment_2.h"


namespace geometry
{
	template<typename real>
	bool segment_intersect(const Segment_2<real>& s1,
						   const Segment_2<real>& s2);
	template<typename real>
	Point_2<real> line_intersection(const Segment_2<real>& s1,
									const Segment_2<real>& s2);
	template<typename real>
	real x_intersection(const Segment_2<real>& s,
						const real& y);


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename real>
	bool segment_intersect(const Segment_2<real>& s1,
						   const Segment_2<real>& s2)
	{
		real a = weird_det(s1.p1, s1.p2, s2.p1) *
				 weird_det(s1.p1, s1.p2, s2.p2);
		real b = weird_det(s2.p1, s2.p2, s1.p1) *
				 weird_det(s2.p1, s2.p2, s1.p2);
		return a <=0 && b <= 0;
	}

	template<typename real>
	Point_2<real>
	line_intersection(const Segment_2<real>& s1,
					  const Segment_2<real>& s2)
	{
		Point_2<real> v1 = s1.p2 - s1.p1;
		real a1 = v1.y;
		real b1 = -v1.x;
		real c1 = a1 * s1.p1.x + b1 * s1.p1.y;

		Point_2<real> v2 = s2.p2 - s2.p1;
		real a2 = v2.y;
		real b2 = -v2.x;
		real c2 = a2 * s2.p1.x + b2 * s2.p1.y;

		real x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
		real y = (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
		return Point_2<real>(x, y);
	}

	template<typename real>
	real x_intersection(const Segment_2<real>& s,
						const real& y)
	{
		if (s.p1.y == s.p2.y)
		{
			if (s.p1.y != y)
			{
				std::cerr << "Error : Line does not intersect the line y = "
						  << y << std::endl;
				return 0;
			}
			return std::min(s.p1.x, s.p2.x);
		}

		real a = s.p2.y - s.p1.y;
		real b = s.p1.x - s.p2.x;
		real c = -(a * s.p1.x + b * s.p1.y);
		return -(c + b * y) / a;
	}
}