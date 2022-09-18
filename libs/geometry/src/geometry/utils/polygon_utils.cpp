#include "geometry/utils/polygon_utils.h"


namespace geometry
{
	bool clockwise_orientation(const polygon& P)
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
								P[(n + i_max - 1) % n],
								P[i_max]);
	}
}