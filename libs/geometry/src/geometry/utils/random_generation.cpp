#include "geometry/utils/random_generation.h"


namespace geometry
{
	Number_generator::Number_generator(unsigned long seed) :
			generator(std::default_random_engine(seed)),
			distribution(std::normal_distribution<dist_number>(0, 1))
	{}

	number Number_generator::next_number(const dist_number& inf,
										 const dist_number& sup)
	{
		dist_number a = distribution(generator);
		return {integer(inf + a * (sup - inf))};
	}

	point_2 Number_generator::random_point_2()
	{
		number x = next_number();
		number y = next_number();
		return {x, y};
	}

	segment_2 Number_generator::random_segment_2()
	{
		point_2 p1 = random_point_2();
		point_2 p2 = random_point_2();
		return {p1, p2};
	}

	std::vector<point_2> Number_generator::random_point_2_set(unsigned n)
	{
		std::vector<point_2> points;
		for (unsigned i = 0; i < n; ++i)
		{
			points.push_back(random_point_2());
		}
		return points;
	}

	std::vector<segment_2> Number_generator::random_segment_2_set(unsigned n)
	{
		std::vector<segment_2> segments;
		for (unsigned i = 0; i < n; ++i)
		{
			segments.push_back(random_segment_2());
		}
		return segments;
	}
}