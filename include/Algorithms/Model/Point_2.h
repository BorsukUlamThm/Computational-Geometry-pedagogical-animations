#pragma once

/** @cond */
#include <ostream>
/** @endcond */


namespace algorithms
{
	/*!
	 * A Point_2 is a 2D point defined by its (x, y) coordinate
	 */
	template<typename Real>
	struct Point_2
	{
		Real x {};
		Real y {};

		Point_2() = default;
		Point_2(const Real& x,
				const Real& y);
		~Point_2() = default;
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Real>
	Point_2<Real>::Point_2(const Real& x,
						   const Real& y):
			x(x),
			y(y)
	{}

	template<typename Real>
	bool operator==(const Point_2<Real>& p,
					const Point_2<Real>& q)
	{
		return p.x == q.x && p.y == q.y;
	}
}