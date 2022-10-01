#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	multi_rational det(const point_2& p,
					   const point_2& q)
	{
		multi_rational px (p.x);
		multi_rational py (p.y);
		multi_rational qx (q.x);
		multi_rational qy (q.y);

		return px * qy - py * qx;
	}

	multi_rational orientation_det(const point_2& p,
								   const point_2& q,
								   const point_2& r)
	{
		multi_rational a = det(q, r);
		multi_rational b = det(p, r);
		multi_rational c = det(p, q);

		return a - b + c;
	}

	bool point_below_point(const point_2& p,
						   const point_2& q)
	{
		if (p.y == q.y)
		{ return p.x >= q.x; }
		return p.y < q.y;
	}

	bool point_above_point(const point_2& p,
						   const point_2& q)
	{
		if (p.y == q.y)
		{ return p.x <= q.x; }
		return p.y > q.y;
	}

	bool point_left_point(const point_2& p,
						  const point_2& q)
	{
		if (p.x == q.x)
		{ return p.y >= q.y; }
		return p.x < q.x;
	}

	bool point_right_point(const point_2& p,
						   const point_2& q)
	{
		if (p.x == q.x)
		{ return p.y <= q.y; }
		return p.x > q.x;
	}

	bool point_on_line(const point_2& p,
					   const point_2& l1,
					   const point_2& l2)
	{
		return orientation_det(p, l1, l2) == multi_rational(0);
	}

	bool point_left_line(const point_2& p,
						 const point_2& l1,
						 const point_2& l2)
	{
		return orientation_det(p, l1, l2) >= multi_rational(0);
	}

	bool point_right_line(const point_2& p,
						  const point_2& l1,
						  const point_2& l2)
	{
		return orientation_det(p, l1, l2) <= multi_rational(0);
	}

	bool point_strictly_left_line(const point_2& p,
								  const point_2& l1,
								  const point_2& l2)
	{
		return orientation_det(p, l1, l2) > multi_rational(0);
	}

	bool point_strictly_right_line(const point_2& p,
								   const point_2& l1,
								   const point_2& l2)
	{
		return orientation_det(p, l1, l2) < multi_rational(0);
	}
}