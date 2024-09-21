#pragma once

#include "geometry/utils/algebra.h"
#include "graphics/model/global_variables.h"


namespace gr = graphics;

namespace geometry
{
	struct number
	{
		// Rational field for now
		// We will try to make the field of constructible numbers

		rational val {};

		number() = default;
		number(int n);
		number(int num, int den);
		number(float x);
		number(rational  x);

		int sign() const;

		explicit operator gr::Coordinate() const;
	};

	bool operator==(const number& x,
					const number& y);
	bool operator!=(const number& x,
					const number& y);
	bool operator>=(const number& x,
					const number& y);
	bool operator<=(const number& x,
					const number& y);
	bool operator>(const number& x,
				   const number& y);
	bool operator<(const number& x,
				   const number& y);

	number operator+(const number& x,
					 const number& y);
	number operator-(const number& x,
					 const number& y);
	number operator-(const number& x);
	number operator*(const number& x,
					 const number& y);
	number operator/(const number& x,
					 const number& y);
}