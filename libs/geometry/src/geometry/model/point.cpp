#include "geometry/model/point.h"


namespace geometry
{
	point::point(const real& x,
				 const real& y) :
			x(x),
			y(y)
	{}

	bool operator==(const point& p,
					const point& q)
	{
		return p.x == q.x && p.y == q.y;
	}

	bool operator!=(const point& p,
					const point& q)
	{
		return p.x != q.x || p.y != q.y;
	}

	point operator+(const point& p,
					const point& q)
	{
		return {p.x + q.x, p.y + q.y};
	}

	point operator-(const point& p,
					const point& q)
	{
		return {p.x - q.x, p.y - q.y};
	}

	point operator-(const point& p)
	{
		return {-p.x, -p.y};
	}

	point operator*(real a,
					const point& p)
	{
		return {a * p.x, a * p.y};
	}
}