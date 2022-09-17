#pragma once

#include "real.h"


namespace geometry
{
	/*!
	 * A point is a 2D point defined by its (x, y) coordinate
	 */
	struct point
	{
		real x {};
		real y {};

		point() = default;
		point(const real& x,
			  const real& y);
		~point() = default;
	};

	bool operator==(const point& p,
					const point& q);
	bool operator!=(const point& p,
					const point& q);

	point operator+(const point& p,
					const point& q);
	point operator-(const point& p,
					const point& q);
	point operator-(const point& p);
	point operator*(real a,
					const point& p);
}