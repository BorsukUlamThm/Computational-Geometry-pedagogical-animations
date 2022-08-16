#pragma once

#include "geometry/Model/Point_2.h"
#include "geometry/Tools/Random_generation.h"
#include "geometry/Model/Serialization.h"
#include "graphics/View/Acquisition_canvas.h"


namespace chs
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::Point_2<int> point;
	typedef std::vector<point> point_set;

	enum Input_type
	{
		RANDOM,
		ACQUISITION,
		FILE
	};

	struct Convex_hull_option
	{
		Input_type input_type = RANDOM;
		unsigned nb_random_points = 50;
		unsigned long seed = time_seed;
		std::string input_path{};
	};

	Convex_hull_option process_command_line(int argc, char** argv)
	{
		Convex_hull_option opt;

		for (unsigned i = 0; i < argc; ++i)
		{
			if (argv[i][0] != '-')
			{
				continue;
			}

			if (std::string(argv[i]) == "-a")
			{
				opt.input_type = ACQUISITION;
				continue;
			}
			if (std::string(argv[i]) == "-r")
			{
				opt.input_type = RANDOM;
				++i;
				if (i >= argc)
				{
					std::cerr << "invalid -r parameter, missing"
							  << " number of random points"
							  << std::endl;
					continue;
				}

				try
				{
					opt.nb_random_points = std::stoi(std::string(argv[i]));
				}
				catch (const std::invalid_argument& ia)
				{
					std::cerr << "invalid -r parameter, missing"
							  << " number of random points"
							  << std::endl;
					--i;
				}
			}

			if (std::string(argv[i]) == "-s")
			{
				++i;
				if (i >= argc)
				{
					std::cerr << "invalid -s parameter, missing seed"
							  << std::endl;
					continue;
				}

				try
				{
					opt.seed = std::stoi(std::string(argv[i]));
				}
				catch (const std::invalid_argument& ia)
				{
					std::cerr << "invalid -s parameter, missing seed"
							  << std::endl;
					--i;
				}
			}

			if (std::string(argv[i]) == "-i")
			{
				opt.input_type = FILE;
				++i;
				if (i >= argc)
				{
					std::cerr << "invalid -s parameter, missing seed"
							  << std::endl;
					continue;
				}

				opt.input_path = std::string(argv[i]);
			}

			else
			{
				std::cerr << "unknown " << argv[i] << " option ignored"
						  << std::endl;
			}
		}

		return opt;
	}

	point_set make_point_set(const Convex_hull_option& opt)
	{
		if (opt.input_type == RANDOM)
		{
			std::cout << "initializing " << opt.nb_random_points
					  << " random points"
					  << std::endl << "seed : " << opt.seed << std::endl;

			geo::Number_generator<int> ng(opt.seed);
			return geo::random_point_2_set<int>(opt.nb_random_points, ng);
		}

		if (opt.input_type == ACQUISITION)
		{
			gr::Acquisition_canvas canvas;
			canvas.set_title("Convex hull - acquisition");
			canvas.add_point_acquisition();
			gr::Acquisitions acquisitions = canvas.acquire_buffer();

			point_set P;
			for (unsigned i = 0; i < acquisitions[0]->get_size(); ++i)
			{
				auto p = std::dynamic_pointer_cast<gr::Point_obj>
						(acquisitions[0]->get(i));
				P.emplace_back(int(p->abscissa),
							   int(p->ordinate));
			}

			return P;
		}

		return geo::load_point_2_set<int>(opt.input_path);
	}
}