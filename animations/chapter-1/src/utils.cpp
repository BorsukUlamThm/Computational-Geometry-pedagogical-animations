#include "../include/utils.h"


namespace convex_hull_utils
{
	Options process_command_line(int argc,
								 char** argv)
	{
		Options opt;
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
						  << "missing number of random points"
						  << std::endl;
			}
			else
			{
				std::string nb = program_options[RANDOM_OPT].parameters[0];
				try
				{
					opt.nb_random_points = std::stoi(nb);
				}
				catch (const std::invalid_argument& ia)
				{
					std::cerr << "[options] "
							  << "invalid --random -r parameter, "
							  << " couldn't read "
							  << nb
							  << " as a number of random points"
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
			case FILE:
				std::cout << "file ("
						  << opt.input_file
						  << ")";
				break;
			case ACQUISITION:
				std::cout << "acquisition";
				break;
			case RANDOM:
				std::cout << "random ("
						  << opt.nb_random_points
						  << " points, with seed "
						  << opt.seed
						  << ")";
				break;
		}
		std::cout << std::endl << std::endl;

		return opt;
	}

	point_set make_point_set(const Options& opt)
	{
		if (opt.input_type == RANDOM)
		{
			geo::Number_generator ng(opt.seed);
			return ng.random_point_2_set(opt.nb_random_points);
		}

		if (opt.input_type == ACQUISITION)
		{
			gr::Acquisition_canvas canvas;
			canvas.set_title("Convex Hull - acquisition");
			canvas.add_point_acquisition();
			gr::Acquisitions acquisitions = canvas.acquire_buffer();

			point_set P;
			for (auto& p : acquisitions[0]->get_objects<gr::Point_obj>())
			{
				P.emplace_back(geo::number(p.abscissa),
							   geo::number(p.ordinate));
			}

			return P;
		}

		return geo::load_point_2_set(opt.input_file);
	}
}