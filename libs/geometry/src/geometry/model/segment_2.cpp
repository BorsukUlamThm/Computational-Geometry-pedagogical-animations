#include "geometry/model/segment_2.h"


namespace geometry
{
	segment_2::segment_2(const point_2& p1,
						 const point_2& p2) :
			p1(p1),
			p2(p2)
	{}

	segment_2::segment_2(const number& p1_x,
						 const number& p1_y,
						 const number& p2_x,
						 const number& p2_y) :
			p1(p1_x, p1_y),
			p2(p2_x, p2_y)
	{}

	bool operator==(const segment_2& s1,
					const segment_2& s2)
	{
		return s1.p1 == s2.p1 && s1.p2 == s2.p2;
	}

	number segment_2::squared_norm() const
	{
		return (p1 - p2).squared_norm();
	}
}