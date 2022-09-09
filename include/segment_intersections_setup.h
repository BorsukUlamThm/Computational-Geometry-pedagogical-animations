#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "geometry/model/Segment_2.h"
#include "geometry/utils/random_generation.h"
#include "geometry/model/serialization.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"


namespace chap2_segment_intersections
{
	namespace geo = geometry;

	typedef boost::rational<boost::multiprecision::cpp_int> rational;
	typedef geo::Point_2<rational> point;
	typedef geo::Segment_2<rational> segment;
	typedef std::vector<segment> segment_set;


	enum Input_type
	{
		RANDOM,
		ACQUISITION,
		FILE
	};

	struct Segment_intersections_options
	{
		Input_type input_type = FILE;
		unsigned nb_random_segments = 20;
		unsigned long seed = time_seed;
		std::string input_file;
	};

	Segment_intersections_options process_command_line(int argc,
													   char** argv)
	{
		Segment_intersections_options opt;
		utils::Program_options program_options;

		enum Options
		{
			INPUT_FILE_OPT,
			ACQUISITION_OPT,
			RANDOM_OPT,
			SEED_OPT
		};

		program_options.add_option("input_file", "i");
		program_options.add_option("acquisition", "a");
		program_options.add_option("random", "r");
		program_options.add_option("seed", "s");
		program_options.parse_command_line(argc, argv);

		if (program_options[INPUT_FILE_OPT].is_used)
		{
			opt.input_type = FILE;
			if (program_options[INPUT_FILE_OPT].parameters.empty())
			{
				std::cerr << "[options] "
						  << "invalid --input_file -i parameter, "
						  << "missing input file"
						  << std::endl;
			}
			else
			{
				opt.input_file = program_options[INPUT_FILE_OPT].parameters[0];
			}
		}
		if (program_options[ACQUISITION_OPT].is_used)
		{
			opt.input_type = ACQUISITION;
		}
		if (program_options[RANDOM_OPT].is_used)
		{
			opt.input_type = RANDOM;
			if (program_options[RANDOM_OPT].parameters.empty())
			{
				std::cerr << "[options] "
						  << "invalid --random -r parameter, "
						  << "missing number of random segments"
						  << std::endl;
			}
			else
			{
				std::string nb = program_options[RANDOM_OPT].parameters[0];
				try
				{
					opt.nb_random_segments = std::stoi(nb);
				}
				catch (const std::invalid_argument& ia)
				{
					std::cerr << "[options] "
							  << "invalid --random -r parameter, "
							  << " couldn't read "
							  << nb
							  << " as a number of random segments"
							  << std::endl;
				}
			}
		}
		if (program_options[SEED_OPT].is_used)
		{
			if (program_options[SEED_OPT].parameters.empty())
			{
				std::cerr << "[options] "
						  << "invalid --seed -s parameter, "
						  << "missing seed"
						  << std::endl;
			}
			else
			{
				std::string seed = program_options[SEED_OPT].parameters[0];
				try
				{
					opt.seed = std::stoi(seed);
				}
				catch (const std::invalid_argument& ia)
				{
					std::cerr << "[options] "
							  << "invalid --seed -s parameter, "
							  << " couldn't read "
							  << seed
							  << "as a number seed"
							  << std::endl;
				}
			}
		}

		std::cout << std::endl
				  << "input type : ";
		switch (opt.input_type)
		{
			case (FILE):
				std::cout << "file ("
						  << opt.input_file
						  << ")";
				break;
			case (ACQUISITION):
				std::cout << "acquisition";
				break;
			case (RANDOM):
				std::cout << "random ("
						  << opt.nb_random_segments
						  << " segments, with seed "
						  << opt.seed
						  << ")";
				break;
		}
		std::cout << std::endl << std::endl;

		return opt;
	}

	segment_set make_segment_set(const Segment_intersections_options& opt)
	{
		if (opt.input_type == RANDOM)
		{
			geo::Number_generator<int> ng(opt.seed);
			auto vec = geo::random_segment_2_set<int>(opt.nb_random_segments,
													  ng);
			segment_set set;
			for (auto& s : vec)
			{
				rational x1 (s.p1.x);
				rational y1 (s.p1.y);
				rational x2 (s.p2.x);
				rational y2 (s.p2.y);
				set.emplace_back(x1, y1, x2, y2);
			}
			return set;
		}

		if (opt.input_type == ACQUISITION)
		{
			gr::Acquisition_canvas canvas;
			canvas.set_title("Segment Intersection - acquisition");
			canvas.add_segment_acquisition();
			gr::Acquisitions acquisitions = canvas.acquire_buffer();

			segment_set S;
			for (auto& s : acquisitions[0]->get_objects<gr::Segment_obj>())
			{
				S.emplace_back(rational(int(s.origin.abscissa)),
							   rational(int(s.origin.ordinate)),
							   rational(int(s.destination.abscissa)),
							   rational(int(s.destination.ordinate)));
			}

			return S;
		}

		auto vec = geo::load_segment_2_set<int>(opt.input_file);
		segment_set set;
		for (auto& s : vec)
		{
			rational x1 (s.p1.x);
			rational y1 (s.p1.y);
			rational x2 (s.p2.x);
			rational y2 (s.p2.y);
			set.emplace_back(x1, y1, x2, y2);
		}
		return set;
	}
}