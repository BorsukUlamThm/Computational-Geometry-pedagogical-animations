#pragma once

#include <vector>
#include <chrono>
#include <random>
#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"


namespace geometry
{
#define clock std::chrono::system_clock
#define time_seed (clock::now().time_since_epoch().count() % 1000000)

	/*!
	 * A Number_generator will generate random numbers using a normal
	 * distribution. A seed can be provided to the constructor, by default it is
	 * determined by the clock
	 */
	class Number_generator
	{
		typedef double dist_number;

		std::default_random_engine generator;
		std::normal_distribution<dist_number> distribution;

	public:
		explicit Number_generator(unsigned long seed = time_seed);

		/**
		 * @return a number following a normal distribution on [inf, sup]
		 */
		real next_number(const dist_number& inf = -50,
						 const dist_number& sup = 50);

		/*!
		 * @return a random point
		 */
		point_2 random_point_2();
		/*!
		 * @return a random segment
		 */
		segment_2 random_segment_2();
		/*!
		 * @return a random point vector
		 */
		std::vector<point_2> random_point_2_set(unsigned n);
		/*!
		 * @return a random segment vector
		 */
		std::vector<segment_2> random_segment_2_set(unsigned n);
	};
}