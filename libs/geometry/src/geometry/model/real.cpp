#include "geometry/model/real.h"

#include <utility>


namespace geometry
{
	real::real(int n) :
			val(n)
	{ make_approx(); }

	real::real(int num, int den) :
			val(rational(num, den))
	{ make_approx(); }

	real::real(float x) :
			val(int(x))
	{ make_approx(); }

	real::real(rational x) :
			val(std::move(x))
	{ make_approx(); }

	int real::sign() const
	{
		if (val.numerator() == 0)
		{
			return 0;
		}
		if (val.numerator() > 0)
		{
			return (val.denominator() > 0 ? 1 : -1);
		}
		return (val.denominator() > 0 ? -1 : 1);
	}

	void real::make_approx()
	{
		approx = boost::rational_cast<approx_t>(val);
	}

	real::operator gr::Coordinate() const
	{
		return boost::rational_cast<gr::Coordinate>(val);
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
		return {x.val + y.val};
	}

	real operator-(const real& x,
				   const real& y)
	{
		return {x.val - y.val};
	}

	real operator-(const real& x)
	{
		return {-x.val};
	}

	real operator*(const real& x,
				   const real& y)
	{
		return {x.val * y.val};
	}

	real operator/(const real& x,
				   const real& y)
	{
		return {x.val / y.val};
	}
}