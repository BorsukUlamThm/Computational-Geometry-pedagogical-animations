#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "geometry/model/Segment_2.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/random_generation.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/utils/AVL.h"


namespace segment_intersections_utils
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef boost::rational<boost::multiprecision::cpp_int> rational;
	typedef geo::Point_2<rational> point;
	typedef geo::Segment_2<rational> segment;
	typedef std::vector<segment> segment_set;

	enum Figures
	{
		SEGMENTS,
		EVENT,
		INTERSECTIONS,
		NB_FIGURES
	};



	/// TREE

	struct tree_cmp
	{
		rational y_line {};
		bool just_above = true;
		segment_set& S;

		explicit tree_cmp(segment_set& S);

		bool operator()(unsigned i, unsigned j) const;
		bool are_equal(unsigned i, unsigned j) const;
	};

	typedef geo::AVL_tree<unsigned, tree_cmp> tree;


	/// COMMAND LINE OPTIONS

	enum Input_type
	{
		RANDOM,
		ACQUISITION,
		FILE
	};

	struct Options
	{
		Input_type input_type = FILE;
		unsigned nb_random_segments = 20;
		unsigned long seed = time_seed;
		std::string input_file;
	};

	Options process_command_line(int argc,
								 char** argv);

	segment_set make_segment_set(const Options& opt);
}