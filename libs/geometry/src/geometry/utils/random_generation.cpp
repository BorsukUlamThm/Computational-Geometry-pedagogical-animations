#include "geometry/utils/random_generation.h"


namespace geometry
{
	Number_generator::Number_generator(unsigned long seed) :
			generator(std::default_random_engine(seed)),
			distribution(std::normal_distribution<dist_number>(0, 1))
	{}

	real Number_generator::next_number(const dist_number& inf,
									   const dist_number& sup)
	{
		dist_number a = distribution(generator);
		return real(real::integer(inf + a * (sup - inf)));
	}

	point random_point_2(Number_generator& ng)
	{
		real x = ng.next_number();
		real y = ng.next_number();
		return {x, y};
	}

	segment random_segment_2(Number_generator& ng)
	{
		point p1 = random_point_2(ng);
		point p2 = random_point_2(ng);
		return {p1, p2};
	}

	std::vector<point> random_point_2_set(unsigned n,
										  Number_generator& ng)
	{
		std::vector<point> points;
		for (unsigned i = 0; i < n; ++i)
		{
			points.push_back(random_point_2(ng));
		}
		return points;
	}

	std::vector<segment> random_segment_2_set(unsigned n,
											  Number_generator& ng)
	{
		std::vector<segment> segments;
		for (unsigned i = 0; i < n; ++i)
		{
			segments.push_back(random_segment_2(ng));
		}
		return segments;
	}
}