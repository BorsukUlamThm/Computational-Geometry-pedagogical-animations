#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	number det(const point_2& p,
			   const point_2& q)
	{
		return p.x * q.y - p.y * q.x;
	}

	number orientation_det(const point_2& p,
						   const point_2& q,
						   const point_2& r)
	{
		return det(q, r) - det(p, r) + det(p, q);
	}

	bool point_below_point(const point_2& p,
						   const point_2& q)
	{
		if (p.y == q.y)
		{ return p.x >= q.x; }
		return p.y < q.y;
	}

	bool point_below_point(DCEL::vertex* v1,
						   DCEL::vertex* v2)
	{
		if (v1->y == v2->y)
		{ return v1->x >= v2->x; }
		return v1->y < v2->y;
	}

	bool point_above_point(const point_2& p,
						   const point_2& q)
	{
		if (p.y == q.y)
		{ return p.x <= q.x; }
		return p.y > q.y;
	}

	bool point_above_point(DCEL::vertex* v1,
						   DCEL::vertex* v2)
	{
		if (v1->y == v2->y)
		{ return v1->x <= v2->x; }
		return v1->y > v2->y;
	}

	bool point_left_point(const point_2& p,
						  const point_2& q)
	{
		if (p.x == q.x)
		{ return p.y >= q.y; }
		return p.x < q.x;
	}

	bool point_left_point(DCEL::vertex* v1,
						  DCEL::vertex* v2)
	{
		if (v1->x == v2->x)
		{ return v1->y >= v2->y; }
		return v1->x < v2->x;
	}

	bool point_left_point(DCEL::hedge* h1,
						  DCEL::hedge* h2)
	{ return point_left_point(h1->origin, h2->origin); }

	bool point_right_point(const point_2& p,
						   const point_2& q)
	{
		if (p.x == q.x)
		{ return p.y <= q.y; }
		return p.x > q.x;
	}

	bool point_right_point(DCEL::vertex* v1,
						   DCEL::vertex* v2)
	{
		if (v1->x == v2->x)
		{ return v1->y <= v2->y; }
		return v1->x > v2->x;
	}

	bool point_on_line(const point_2& p,
					   const point_2& l1,
					   const point_2& l2)
	{
		return orientation_det(p, l1, l2) == 0;
	}

	bool point_left_line(const point_2& p,
						 const point_2& l1,
						 const point_2& l2)
	{
		return orientation_det(p, l1, l2) >= 0;
	}

	bool point_left_line(DCEL::vertex* v,
						 DCEL::vertex* l1,
						 DCEL::vertex* l2)
	{
		point_2 p(v->x, v->y);
		point_2 pl1(l1->x, l1->y);
		point_2 pl2(l2->x, l2->y);

		return point_left_line(p, pl1, pl2);
	}

	bool point_left_line(DCEL::vertex* v,
						 DCEL::hedge* h)
	{
		return point_left_line(v, h->origin, h->twin->origin);
	}

	bool point_right_line(const point_2& p,
						  const point_2& l1,
						  const point_2& l2)
	{
		return orientation_det(p, l1, l2) <= 0;
	}

	bool point_right_line(DCEL::vertex* v,
						  DCEL::vertex* l1,
						  DCEL::vertex* l2)
	{
		point_2 p(v->x, v->y);
		point_2 pl1(l1->x, l1->y);
		point_2 pl2(l2->x, l2->y);

		return point_right_line(p, pl1, pl2);
	}

	bool point_right_line(DCEL::vertex* v,
						  DCEL::hedge* h)
	{
		return point_right_line(v, h->origin, h->twin->origin);
	}

	bool point_strictly_left_line(const point_2& p,
								  const point_2& l1,
								  const point_2& l2)
	{
		return orientation_det(p, l1, l2) > 0;
	}

	bool point_strictly_right_line(const point_2& p,
								   const point_2& l1,
								   const point_2& l2)
	{
		return orientation_det(p, l1, l2) < 0;
	}
}