#pragma once

#include "real.h"


namespace geometry
{
	/*!
	 * A point is a 2D point defined by its (x, y) coordinate
	 */
	struct point_2
	{
		real x {};
		real y {};

		point_2() = default;
		point_2(const real& x,
				const real& y);
		~point_2() = default;

		real squared_norm() const;
	};

	bool operator==(const point_2& p,
					const point_2& q);
	bool operator!=(const point_2& p,
					const point_2& q);

	point_2 operator+(const point_2& p,
					  const point_2& q);
	point_2 operator-(const point_2& p,
					  const point_2& q);
	point_2 operator-(const point_2& p);
	point_2 operator*(real a,
					  const point_2& p);
}