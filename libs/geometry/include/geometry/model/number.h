#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "graphics/model/global_variables.h"


namespace gr = graphics;

namespace geometry
{
	struct number
	{
		// Rational field for now
		// We will try to make the field of constructible numbers

		typedef boost::multiprecision::cpp_int integer;
		typedef boost::rational<integer> rational;
		typedef float approx_t;

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