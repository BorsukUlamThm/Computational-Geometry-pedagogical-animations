#pragma once

#include <iostream>
#include "Point_comparisons.h"
#include "geometry/Model/Point_2.h"
#include "geometry/Model/Segment_2.h"


namespace geometry
{
	template<typename Real>
	bool segment_intersect(const Segment_2<Real>& s1,
						   const Segment_2<Real>& s2);
	template<typename Real>
	Point_2<Real> line_intersection(const Segment_2<Real>& s1,
									const Segment_2<Real>& s2);
	template<typename Real>
	Real x_intersection(const Segment_2<Real>& s,
						const Real& y);


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Real>
	bool segment_intersect(const Segment_2<Real>& s1,
						   const Segment_2<Real>& s2)
	{
		return weird_det(s1.p1, s1.p2, s2.p1) *
			   weird_det(s1.p1, s1.p2, s2.p2) <= 0;
	}

	template<typename Real>
	Point_2<Real>
	line_intersection(const Segment_2<Real>& s1,
					  const Segment_2<Real>& s2)
	{
		Point_2<Real> v1 = s1.p2() - s1.p1();
		Real a1 = v1.ord();
		Real b1 = -v1.abs();
		Real c1 = a1 * s1.p1().abs() + b1 * s1.p1().ord();

		Point_2<Real> v2 = s2.p2() - s2.p1();
		Real a2 = v2.ord();
		Real b2 = -v2.abs();
		Real c2 = a2 * s2.p1().abs() + b2 * s2.p1().ord();

		Real x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
		Real y = (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
		return point_2<Real>(x, y);
	}

	template<typename Real>
	Real x_intersection(const Segment_2<Real>& s,
						const Real& y)
	{
		if (s.p1.y == s.p2.y)
		{
			if (s.p1.y != y)
			{
				std::cerr << "Error : Line does not intersect x axis for y = "
						  << y << std::endl;
				return 0;
			}
			if (s.p1.x < s.p2.x)
			{
				return s.p1.x;
			}
			return s.p2.x;
		}

		Real a = (s.p2.y - s.p1.y) / (s.p2.x - s.p1.x);
		Real b = s.p1.y - a * s.p1.x;
		return (y - b) / a;
	}
}