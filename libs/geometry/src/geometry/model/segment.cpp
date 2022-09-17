#include "geometry/model/segment.h"


namespace geometry
{
	segment::segment(const point& p1,
					 const point& p2) :
			p1(p1),
			p2(p2)
	{}

	segment::segment(const real& p1_x,
					 const real& p1_y,
					 const real& p2_x,
					 const real& p2_y) :
			p1(p1_x, p1_y),
			p2(p2_x, p2_y)
	{}

	bool operator==(const segment& s1,
					const segment& s2)
	{
		return s1.p1 == s2.p1 && s1.p2 == s2.p2;
	}
}