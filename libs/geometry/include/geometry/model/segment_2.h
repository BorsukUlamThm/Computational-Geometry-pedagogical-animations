#pragma once

#include "point_2.h"


namespace geometry
{
	/*!
	 * A segment is a 2D segment defined by the (x, y) coordinate of its
	 * endpoints
	 */
	struct segment_2
	{
		point_2 p1 {};
		point_2 p2 {};

		segment_2() = default;
		segment_2(const point_2& p1,
				  const point_2& p2);
		segment_2(const real& p1_x,
				  const real& p1_y,
				  const real& p2_x,
				  const real& p2_y);
		~segment_2() = default;
	};

	bool operator==(const segment_2& s1,
					const segment_2& s2);
}