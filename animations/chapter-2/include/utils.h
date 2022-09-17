#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "geometry/model/segment_2.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/random_generation.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/utils/AVL.h"


namespace segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::point_2 point;
	typedef geo::segment_2 segment;
	typedef std::vector<segment> segment_set;

	enum Figures
	{
		SEGMENTS,
		TREE,
		EVENT,
		INTERSECTIONS,
		NB_FIGURES
	};


	enum Input_type
	{
		RANDOM,
		ACQUISITION,
		FILE
	};

	struct Options
	{
		Input_type input_type = RANDOM;
		unsigned nb_random_segments = 20;
		unsigned long seed = time_seed;
		std::string input_file {};
	};

	Options process_command_line(int argc,
								 char** argv);

	segment_set make_segment_set(const Options& opt);
}