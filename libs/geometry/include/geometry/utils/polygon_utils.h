#pragma once

#include <vector>
#include "geometry/model/Point_2.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	template<typename real>
	using Polygon = std::vector<Point_2<real>>;

	template<typename real>
	bool clockwise_orientation(const Polygon<real>& P)
	{
		unsigned n = P.size();
		unsigned i_max = 0;
		for (unsigned i = 0; i < n; ++i)
		{
			if (point_above_point(P[i], P[i_max]))
			{
				i_max = i;
			}
		}

		return point_right_line(P[(i_max + 1) % n],
								P[(n + i_max - 1)%n],
								P[i_max]);
	}
}