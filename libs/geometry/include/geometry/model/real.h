#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>


namespace geometry
{
	typedef boost::multiprecision::cpp_int cpp_int;
	typedef boost::rational<cpp_int> multi_rational;

	struct real
	{
		typedef long integer;
		typedef boost::rational<integer> rational;

		rational val {};

		real() = default;
		real(const integer& n);
		real(const integer& num, const integer& den);
		real(const rational& x);

		int sign() const;

		explicit operator float() const;
		explicit operator multi_rational() const;
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