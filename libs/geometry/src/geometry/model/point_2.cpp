#include "geometry/model/point_2.h"


namespace geometry
{
	point_2::point_2(const number& x,
					 const number& y) :
			x(x),
			y(y)
	{}

	number point_2::squared_norm() const
	{
		return x * x + y * y;
	}


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

	point_2 operator*(const number& a,
					  const point_2& p)
	{
		return {a * p.x, a * p.y};
	}
}