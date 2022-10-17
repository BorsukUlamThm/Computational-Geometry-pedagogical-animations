#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "graphics/model/global_variables.h"


namespace gr = graphics;

namespace geometry
{
	struct real
	{
		typedef boost::multiprecision::cpp_int integer;
		typedef boost::rational<integer> rational;
		typedef float approx_t;

		rational val {};
		approx_t approx {};

		real() = default;
		real(int n);
		real(int num, int den);
		real(float x);
		real(rational  x);

		int sign() const;
		void make_approx();

		explicit operator gr::Coordinate() const;
	};

	bool operator==(const real& x,
					const real& y);
	bool operator!=(const real& x,
					const real& y);
	bool operator>=(const real& x,
					const real& y);
	bool operator<=(const real& x,
					const real& y);
	bool operator>(const real& x,
				   const real& y);
	bool operator<(const real& x,
				   const real& y);

	real operator+(const real& x,
				   const real& y);
	real operator-(const real& x,
				   const real& y);
	real operator-(const real& x);
	real operator*(const real& x,
				   const real& y);
	real operator/(const real& x,
				   const real& y);
}