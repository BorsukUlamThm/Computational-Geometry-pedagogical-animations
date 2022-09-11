#pragma once


namespace geometry
{
	/*!
	 * A Point_2 is a 2D point defined by its (x, y) coordinate
	 */
	template<typename real>
	struct Point_2
	{
		real x {};
		real y {};

		Point_2() = default;
		Point_2(const real& x,
				const real& y);
		~Point_2() = default;
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename real>
	Point_2<real>::Point_2(const real& x,
						   const real& y):
			x(x),
			y(y)
	{}

	template<typename real>
	bool operator==(const Point_2<real>& p,
					const Point_2<real>& q)
	{
		return p.x == q.x && p.y == q.y;
	}

	template<typename real>
	bool operator!=(const Point_2<real>& p,
					const Point_2<real>& q)
	{
		return p.x != q.x || p.y != q.y;
	}

	template<typename real>
	Point_2<real> operator+(Point_2<real> p,
							Point_2<real> q)
	{
		return Point_2<real>(p.x + q.x, p.y + q.y);
	}

	template<typename real>
	Point_2<real> operator-(Point_2<real> p,
							Point_2<real> q)
	{
		return Point_2<real>(p.x - q.x, p.y - q.y);
	}

	template<typename real>
	Point_2<real> operator-(Point_2<real> p)
	{
		return Point_2<real>(-p.x, -p.y);
	}

	template<typename real>
	Point_2<real> operator*(real a,
							Point_2<real> p)
	{
		return Point_2<real>(a * p.x, a * p.y);
	}
}