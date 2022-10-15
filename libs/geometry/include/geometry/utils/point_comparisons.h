#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include "geometry/model/DCEL.h"


namespace geometry
{
	/*!
	 * @return true if p is below q. If they have the same y coordinate, the
	 * right point is considered to be below
	 */
	bool point_below_point(const point_2& p,
						   const point_2& q);
	/*!
	 * @return true if p is above q. If they have the same y coordinate, the
	 * left point is considered to be below
	 */
	bool point_above_point(const point_2& p,
						   const point_2& q);
	/*!
	 * @return true if p is on the left of q. If they have the same x
	 * coordinate, the upper point is considered to be on the left
	 */
	bool point_left_point(const point_2& p,
						  const point_2& q);
	/*!
	 * @return true if v1 is on the left of v2. If they have the same x
	 * coordinate, the upper point is considered to be on the left
	 */
	bool point_left_point(DCEL::vertex* v1,
						  DCEL::vertex* v2);
	/*!
	 * @return true if h1's origin is on the left of v2's. If they have the same
	 * x coordinate, the upper point is considered to be on the left
	 */
	bool point_left_point(DCEL::hedge* h1,
						  DCEL::hedge* h2);
	/*!
	 * @return true if p is on the right of q. If they have the same x
	 * coordinate, the lower point is considered to be on the right
	 */
	bool point_right_point(const point_2& p,
						   const point_2& q);

	/*!
	 * A determinant whose sign allows to determine whether or not the point
	 * r is on the right side or the left side of the line (p, q) oriented from
	 * p to q
	 */
	real orientation_det(const point_2& p,
						 const point_2& q,
						 const point_2& r);
	/*!
	 * @return true if p lies on the line containing l1 and l2
	 */
	bool point_on_line(const point_2& p,
					   const point_2& l1,
					   const point_2& l2);
	/*!
	 * @return true if p lies on the left of line containing l1 and l2, oriented
	 * from l1 to l2
	 */
	bool point_left_line(const point_2& p,
						 const point_2& l1,
						 const point_2& l2);
	/*!
	 * @return true if p lies on the right of line containing l1 and l2,
	 * oriented from l1 to l2
	 */
	bool point_right_line(const point_2& p,
						  const point_2& l1,
						  const point_2& l2);
	/*!
	 * @return true if p lies on the left of line containing l1 and l2, oriented
	 * from l1 to l2, and does not lie on this line
	 */
	bool point_strictly_left_line(const point_2& p,
								  const point_2& l1,
								  const point_2& l2);
	/*!
	 * @return true if p lies on the right of line containing l1 and l2,
	 * oriented from l1 to l2, and does not lie on this line
	 */
	bool point_strictly_right_line(const point_2& p,
								   const point_2& l1,
								   const point_2& l2);
}