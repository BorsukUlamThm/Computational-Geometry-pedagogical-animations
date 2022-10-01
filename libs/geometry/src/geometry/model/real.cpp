#include "geometry/model/real.h"


namespace geometry
{
	real::real(const integer& n) :
			val(n)
	{}

	real::real(const integer& num, const integer& den) :
			val(rational(num, den))
	{}

	real::real(const rational& x) :
			val(x)
	{}

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

	real::operator float() const
	{
		return boost::rational_cast<float>(val);
	}

	real::operator multi_rational() const
	{
		cpp_int num(val.numerator());
		cpp_int den(val.denominator());
		return {num, den};
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