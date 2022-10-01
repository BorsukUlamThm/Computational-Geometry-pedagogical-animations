#include "geometry/utils/line_intersections.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/model/serialization.h"
#include <cmath>
#include <iostream>


namespace geometry
{
	bool segment_intersect(const segment_2& s1,
						   const segment_2& s2)
	{
		real a = orientation_det(s1.p1, s1.p2, s2.p1) *
				 orientation_det(s1.p1, s1.p2, s2.p2);
		real b = orientation_det(s2.p1, s2.p2, s1.p1) *
				 orientation_det(s2.p1, s2.p2, s1.p2);
		return a <= 0 && b <= 0;
	}

	bool segment_overlap(const segment_2& s1,
						 const segment_2& s2)
	{
		if (!point_on_line(s1.p1, s2.p1, s2.p2) ||
			!point_on_line(s1.p2, s2.p1, s2.p2))
		{ return false; }

		point_2 p = {-(s1.p2 - s1.p1).y, (s1.p2 - s1.p1).x};
		p = s1.p2 + p;

		real a = orientation_det(s1.p2, p, s2.p1);
		real b = orientation_det(s1.p2, p, s2.p2);
		return a * b < 0;
	}

	point_2 line_intersection(const segment_2& s1,
							  const segment_2& s2)
	{
		point_2 v1 = s1.p2 - s1.p1;
		real a1 = v1.y;
		real b1 = -v1.x;
		real c1 = a1 * s1.p1.x + b1 * s1.p1.y;

		point_2 v2 = s2.p2 - s2.p1;
		real a2 = v2.y;
		real b2 = -v2.x;
		real c2 = a2 * s2.p1.x + b2 * s2.p1.y;

		real x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
		real y = (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
		return {x, y};
	}

	real x_intersection(const segment_2& s,
						const real& y)
	{
		if (s.p1.y == s.p2.y)
		{
			if (s.p1.y != y)
			{
				std::cerr << "Error : Line does not intersect the line y = "
						  << y << std::endl;
				return {0};
			}
			return std::min(s.p1.x, s.p2.x);
		}

		real a = s.p2.y - s.p1.y;
		real b = s.p1.x - s.p2.x;
		real c = -(a * s.p1.x + b * s.p1.y);
		return -(c + b * y) / a;
	}

	bool hedges_intersect(DCEL::hedge* h1,
						  DCEL::hedge* h2)
	{
		segment_2 s1(h1->origin->x, h1->origin->y,
					 h1->twin->origin->x, h1->twin->origin->y);
		segment_2 s2(h2->origin->x, h2->origin->y,
					 h2->twin->origin->x, h2->twin->origin->y);

		return segment_intersect(s1, s2);
	}

	bool hedges_overlap(DCEL::hedge* h1,
						DCEL::hedge* h2)
	{
		point_2 a(h1->origin->x, h1->origin->y);
		point_2 b(h1->twin->origin->x, h1->twin->origin->y);
		point_2 c(h2->origin->x, h2->origin->y);
		point_2 d(h2->twin->origin->x, h2->twin->origin->y);

		return segment_overlap({a, b}, {c, d});
	}

	point_2 line_intersection(DCEL::hedge* h1,
							  DCEL::hedge* h2)
	{
		segment_2 s1(h1->origin->x, h1->origin->y,
					 h1->twin->origin->x, h1->twin->origin->y);
		segment_2 s2(h2->origin->x, h2->origin->y,
					 h2->twin->origin->x, h2->twin->origin->y);

		return line_intersection(s1, s2);
	}

	real x_intersection(DCEL::hedge* h,
						const real& y)
	{
		segment_2 s(h->origin->x, h->origin->y,
					h->twin->origin->x, h->twin->origin->y);

		return x_intersection(s, y);
	}
}