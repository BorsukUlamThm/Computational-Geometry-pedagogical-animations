#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>


namespace geometry
{
	typedef boost::multiprecision::cpp_int integer;
	typedef boost::rational<integer> rational;
}