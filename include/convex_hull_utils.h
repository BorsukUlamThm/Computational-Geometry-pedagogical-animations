#pragma once

#include "geometry/model/Point_2.h"
#include "geometry/utils/random_generation.h"
#include "geometry/model/serialization.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"


namespace convex_hull_utils
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::Point_2<int> point;
	typedef std::vector<point> point_set;
	typedef std::vector<point> convex_hull;

	enum Input_type
	{
		RANDOM,
		ACQUISITION,
		FILE
	};

	struct Options
	{
		Input_type input_type = RANDOM;
		unsigned nb_random_points = 500;
		unsigned long seed = time_seed;
		std::string input_file {};
	};

	Options process_command_line(int argc,
								 char** argv);

	point_set make_point_set(const Options& opt);
}