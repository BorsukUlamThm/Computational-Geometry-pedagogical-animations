#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	real det(const point& p,
			 const point& q)
	{
		return p.x * q.y - p.y * q.x;
	}

	real orientation_det(const point& p,
						 const point& q,
						 const point& r)
	{
		return det(q, r) - det(p, r) + det(p, q);
	}

	bool point_below_point(const point& p,
						   const point& q)
	{
		if (p.y == q.y)
		{ return p.x >= q.x; }
		return p.y < q.y;
	}

	bool point_above_point(const point& p,
						   const point& q)
	{
		if (p.y == q.y)
		{ return p.x <= q.x; }
		return p.y > q.y;
	}

	bool point_left_point(const point& p,
						  const point& q)
	{
		if (p.x == q.x)
		{ return p.y >= q.y; }
		return p.x < q.x;
	}

	bool point_right_point(const point& p,
						   const point& q)
	{
		if (p.x == q.x)
		{ return p.y <= q.y; }
		return p.x > q.x;
	}

	bool point_on_line(const point& p,
					   const point& l1,
					   const point& l2)
	{
		return orientation_det(p, l1, l2) == real(0);
	}

	bool point_left_line(const point& p,
						 const point& l1,
						 const point& l2)
	{
		return orientation_det(p, l1, l2) >= real(0);
	}

	bool point_right_line(const point& p,
						  const point& l1,
						  const point& l2)
	{
		return orientation_det(p, l1, l2) <= real(0);
	}

	bool point_strictly_left_line(const point& p,
								  const point& l1,
								  const point& l2)
	{
		return orientation_det(p, l1, l2) > real(0);
	}

	bool point_strictly_right_line(const point& p,
								   const point& l1,
								   const point& l2)
	{
		return orientation_det(p, l1, l2) < real(0);
	}
}