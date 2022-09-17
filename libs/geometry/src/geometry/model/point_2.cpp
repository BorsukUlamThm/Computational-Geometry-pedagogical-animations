#include "geometry/model/point_2.h"


namespace geometry
{
	point_2::point_2(const real& x,
					 const real& y) :
			x(x),
			y(y)
	{}

	bool operator==(const point_2& p,
					const point_2& q)
	{
		return p.x == q.x && p.y == q.y;
	}

	bool operator!=(const point_2& p,
					const point_2& q)
	{
		return p.x != q.x || p.y != q.y;
	}

	point_2 operator+(const point_2& p,
					  const point_2& q)
	{
		return {p.x + q.x, p.y + q.y};
	}

	point_2 operator-(const point_2& p,
					  const point_2& q)
	{
		return {p.x - q.x, p.y - q.y};
	}

	point_2 operator-(const point_2& p)
	{
		return {-p.x, -p.y};
	}

	point_2 operator*(real a,
					  const point_2& p)
	{
		return {a * p.x, a * p.y};
	}
}