#include "geometry/utils/line_intersections.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/model/serialization.h"
#include <iostream>


namespace geometry
{
	bool segment_intersect(const segment& s1,
						   const segment& s2)
	{
		real a = orientation_det(s1.p1, s1.p2, s2.p1) *
				 orientation_det(s1.p1, s1.p2, s2.p2);
		real b = orientation_det(s2.p1, s2.p2, s1.p1) *
				 orientation_det(s2.p1, s2.p2, s1.p2);
		return a <= real(0) && b <= real(0);
	}

	point line_intersection(const segment& s1,
							const segment& s2)
	{
		point v1 = s1.p2 - s1.p1;
		real a1 = v1.y;
		real b1 = -v1.x;
		real c1 = a1 * s1.p1.x + b1 * s1.p1.y;

		point v2 = s2.p2 - s2.p1;
		real a2 = v2.y;
		real b2 = -v2.x;
		real c2 = a2 * s2.p1.x + b2 * s2.p1.y;

		real x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
		real y = (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
		return {x, y};
	}

	real x_intersection(const segment& s,
						const real& y)
	{
		if (s.p1.y == s.p2.y)
		{
			if (s.p1.y != y)
			{
				std::cerr << "Error : Line does not intersect the line y = "
						  << y << std::endl;
				return real(0);
			}
			return std::min(s.p1.x, s.p2.x);
		}

		real a = s.p2.y - s.p1.y;
		real b = s.p1.x - s.p2.x;
		real c = -(a * s.p1.x + b * s.p1.y);
		return -(c + b * y) / a;
	}
}