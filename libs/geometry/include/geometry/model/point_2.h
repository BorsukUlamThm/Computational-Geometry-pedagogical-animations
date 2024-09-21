#pragma once

#include "number.h"


namespace geometry
{
	/*!
	 * A point is a 2D point defined by its (x, y) coordinate
	 */
	struct point_2
	{
		number x {};
		number y {};

		point_2() = default;
		point_2(const number& x,
				const number& y);
		~point_2() = default;

		number squared_norm() const;
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
	point_2 operator*(const number& a,
					  const point_2& p);
}