#include "geometry/model/number.h"

#include <utility>


namespace geometry
{
	number::number(int n) :
			val(n)
	{}

	number::number(int num, int den) :
			val(rational(num, den))
	{}

	number::number(float x) :
			val(int(x))
	{}

	number::number(rational x) :
			val(std::move(x))
	{}

	int number::sign() const
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

	number::operator gr::Coordinate() const
	{
		return boost::rational_cast<gr::Coordinate>(val);
	}

	bool operator==(const number& x,
					const number& y)
	{
		return x.val == y.val;
	}

	bool operator!=(const number& x,
					const number& y)
	{
		return x.val != y.val;
	}

	bool operator>=(const number& x,
					const number& y)
	{
		return x.val >= y.val;
	}

	bool operator<=(const number& x,
					const number& y)
	{
		return x.val <= y.val;
	}

	bool operator>(const number& x,
				   const number& y)
	{
		return x.val > y.val;
	}

	bool operator<(const number& x,
				   const number& y)
	{
		return x.val < y.val;
	}

	number operator+(const number& x,
					 const number& y)
	{
		return {x.val + y.val};
	}

	number operator-(const number& x,
					 const number& y)
	{
		return {x.val - y.val};
	}

	number operator-(const number& x)
	{
		return {-x.val};
	}

	number operator*(const number& x,
					 const number& y)
	{
		return {x.val * y.val};
	}

	number operator/(const number& x,
					 const number& y)
	{
		return {x.val / y.val};
	}
}