#pragma once

#include "point.h"


namespace geometry
{
	/*!
	 * A segment is a 2D segment defined by the (x, y) coordinate of its
	 * endpoints
	 */
	struct segment
	{
		point p1 {};
		point p2 {};

		segment() = default;
		segment(const point& p1,
				const point& p2);
		segment(const real& p1_x,
				const real& p1_y,
				const real& p2_x,
				const real& p2_y);
		~segment() = default;
	};

	bool operator==(const segment& s1,
					const segment& s2);
}