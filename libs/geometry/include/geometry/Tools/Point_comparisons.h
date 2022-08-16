#pragma once

#include "geometry/Model/Point_2.h"
#include "geometry/Model/Segment_2.h"


namespace geometry
{
	/*!
	 * @return true if p is below q. If they have the same y coordinate, the
	 * right point is considered to be below
	 */
	template<typename Real>
	bool point_below_point(const Point_2<Real>& p,
						   const Point_2<Real>& q);
	/*!
	 * @return true if p is above q. If they have the same y coordinate, the
	 * left point is considered to be below
	 */
	template<typename Real>
	bool point_above_point(const Point_2<Real>& p,
						   const Point_2<Real>& q);
	/*!
	 * @return true if p is on the left of q. If they have the same x
	 * coordinate, the upper point is considered to be on the left
	 */
	template<typename Real>
	bool point_left_point(const Point_2<Real>& p,
						  const Point_2<Real>& q);
	/*!
	 * @return true if p is on the right of q. If they have the same x
	 * coordinate, the lower point is considered to be on the right
	 */
	template<typename Real>
	bool point_right_point(const Point_2<Real>& p,
						   const Point_2<Real>& q);

	/*!
	 * @return true if p lies on the line containing l1 and l2
	 */
	template<typename Real>
	bool point_on_line(const Point_2<Real>& p,
					   const Point_2<Real>& l1,
					   const Point_2<Real>& l2);
	/*!
	 * @return true if p lies on the left of line containing l1 and l2, oriented
	 * from l1 to l2
	 */
	template<typename Real>
	bool point_left_line(const Point_2<Real>& p,
						 const Point_2<Real>& l1,
						 const Point_2<Real>& l2);
	/*!
	 * @return true if p lies on the right of line containing l1 and l2,
	 * oriented from l1 to l2
	 */
	template<typename Real>
	bool point_right_line(const Point_2<Real>& p,
						  const Point_2<Real>& l1,
						  const Point_2<Real>& l2);
	/*!
	 * @return true if p lies on the left of line containing l1 and l2, oriented
	 * from l1 to l2, and does not lie on this line
	 */
	template<typename Real>
	bool point_strictly_left_line(const Point_2<Real>& p,
								  const Point_2<Real>& l1,
								  const Point_2<Real>& l2);
	/*!
	 * @return true if p lies on the right of line containing l1 and l2,
	 * oriented from l1 to l2, and does not lie on this line
	 */
	template<typename Real>
	bool point_strictly_right_line(const Point_2<Real>& p,
								   const Point_2<Real>& l1,
								   const Point_2<Real>& l2);


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Real>
	Real det(const Point_2<Real>& p,
			 const Point_2<Real>& q)
	{
		return p.x * q.y - p.y * q.x;
	}

	/*!
	 * Weird determinant whose sign allows to determine whether or not the point
	 * r is on the right side or the left side of the line (p, q) oriented from
	 * p to q
	 */
	template<typename Real>
	Real weird_det(const Point_2<Real>& p,
				   const Point_2<Real>& q,
				   const Point_2<Real>& r)
	{
		return det(q, r) - det(p, r) + det(p, q);
	}

	template<typename Real>
	bool point_below_point(const Point_2<Real>& p,
						   const Point_2<Real>& q)
	{
		if (p.y == q.y)
		{ return p.x >= q.x; }
		return p.y < q.y;
	}

	template<typename Real>
	bool point_above_point(const Point_2<Real>& p,
						   const Point_2<Real>& q)
	{
		if (p.y == q.y)
		{ return p.x <= q.x; }
		return p.y > q.y;
	}

	template<typename Real>
	bool point_left_point(const Point_2<Real>& p,
						  const Point_2<Real>& q)
	{
		if (p.x == q.x)
		{ return p.y >= q.y; }
		return p.x < q.x;
	}

	template<typename Real>
	bool point_right_point(const Point_2<Real>& p,
						   const Point_2<Real>& q)
	{
		if (p.x == q.x)
		{ return p.y <= q.y; }
		return p.x > q.x;
	}

	template<typename Real>
	bool point_on_line(const Point_2<Real>& p,
					   const Point_2<Real>& l1,
					   const Point_2<Real>& l2)
	{
		return weird_det<Real>(p, l1, l2) = 0;
	}

	template<typename Real>
	bool point_left_line(const Point_2<Real>& p,
						 const Point_2<Real>& l1,
						 const Point_2<Real>& l2)
	{
		return weird_det<Real>(p, l1, l2) >= 0;
	}

	template<typename Real>
	bool point_right_line(const Point_2<Real>& p,
						  const Point_2<Real>& l1,
						  const Point_2<Real>& l2)
	{
		return weird_det<Real>(p, l1, l2) <= 0;
	}

	template<typename Real>
	bool point_strictly_left_line(const Point_2<Real>& p,
								  const Point_2<Real>& l1,
								  const Point_2<Real>& l2)
	{
		return weird_det<Real>(p, l1, l2) > 0;
	}

	template<typename Real>
	bool point_strictly_right_line(const Point_2<Real>& p,
								   const Point_2<Real>& l1,
								   const Point_2<Real>& l2)
	{
		return weird_det<Real>(p, l1, l2) < 0;
	}
}