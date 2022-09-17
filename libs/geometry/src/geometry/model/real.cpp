#include "geometry/model/real.h"


namespace geometry
{
	real::real(const integer& n) :
			val(n)
	{}

	real::real(const rational& x) :
			val(x)
	{}

	real::operator float() const
	{
		return boost::rational_cast<float>(val);
	}

	bool operator==(const real& x,
					const real& y)
	{
		return x.val == y.val;
	}

	bool operator!=(const real& x,
					const real& y)
	{
		return x.val != y.val;
	}

	bool operator>=(const real& x,
					const real& y)
	{
		return x.val >= y.val;
	}

	bool operator<=(const real& x,
					const real& y)
	{
		return x.val <= y.val;
	}

	bool operator>(const real& x,
				   const real& y)
	{
		return x.val > y.val;
	}

	bool operator<(const real& x,
				   const real& y)
	{
		return x.val < y.val;
	}

	real operator+(const real& x,
				   const real& y)
	{
		return real(x.val + y.val);
	}

	real operator-(const real& x,
				   const real& y)
	{
		return real(x.val - y.val);
	}

	real operator-(const real& x)
	{
		return real(-x.val);
	}

	real operator*(const real& x,
				   const real& y)
	{
		return real(x.val * y.val);
	}

	real operator/(const real& x,
				   const real& y)
	{
		return real(x.val / y.val);
	}
}