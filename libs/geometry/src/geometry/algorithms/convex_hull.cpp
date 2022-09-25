#include "geometry/algorithms/convex_hull.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	struct rotation_order
	{
		point_2 leftmost_point;

		explicit rotation_order(const std::vector<point_2>& P)
		{
			leftmost_point = P[0];
			for (auto& p : P)
			{
				if (point_left_point(p, leftmost_point))
				{
					leftmost_point = p;
				}
			}
		}

		bool operator()(const point_2& p,
						const point_2& q) const
		{
			if (p == q)
			{
				return true;
			}
			if (p == leftmost_point)
			{
				return true;
			}
			if (q == leftmost_point)
			{
				return false;
			}

			return point_left_line(q, leftmost_point, p);
		}
	};

	bool right_turn(const std::vector<point_2>& hull,
					const point_2& p)
	{
		if (hull.size() < 2)
		{
			return false;
		}

		unsigned n = hull.size();
		return point_right_line(p, hull[n - 2], hull[n - 1]);
	}

	DCEL convex_hull(const std::vector<point_2>& P)
	{
		std::vector<point_2> P1(P);
		rotation_order order(P1);
		std::sort(P1.begin(), P1.end(), order);

		unsigned n = P1.size();
		polygon CH;
		CH.push_back(P1[0]);
		CH.push_back(P1[1]);

		for (unsigned i = 2; i < n; ++i)
		{
			while (right_turn(CH, P1[i]))
			{
				CH.pop_back();
			}
			CH.push_back(P1[i]);
		}

		return DCEL_from_polygon(CH);
	}
}