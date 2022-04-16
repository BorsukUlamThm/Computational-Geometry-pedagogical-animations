#ifndef ALPHA_CONVEX_HULL_SETUP_H
#define ALPHA_CONVEX_HULL_SETUP_H


namespace chs
{
typedef alg::Point_2<int> point;
typedef std::vector<point> convex_hull;
typedef std::vector<point> point_set;

struct Convex_hull_option
{
    bool random_input = true;
    unsigned nb_random_points = 50;
    unsigned long seed = time_seed;
};

Convex_hull_option process_command_line(int argc, char** argv)
{
    Convex_hull_option opt;

    for (unsigned i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-a")
        {
            opt.random_input = false;
            continue;
        }
        if (std::string(argv[i]) == "-r")
        {
            opt.random_input = true;
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
            catch(const std::invalid_argument& ia)
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
            catch(const std::invalid_argument& ia)
            {
                std::cerr << "invalid -s parameter, missing seed"
                          << std::endl;
                --i;
            }
        }
    }

    return opt;
}

point_set make_point_set(const Convex_hull_option& opt)
{
    if (opt.random_input)
    {
        std::cout << "initializing " << opt.nb_random_points << " random points"
                  << std::endl << "seed : " << opt.seed << std::endl;

        alg::Normal_number_generator<int> ng(opt.seed);
        return alg::random_point_2_set<int>(opt.nb_random_points, ng);
    }

    gr::Acquisition_canvas canvas;
    canvas.set_title("Convex hull - acquisition");
    canvas.add_point_acquisition();
    gr::Figure fig = canvas.acquire_buffer();

    point_set P;
    for (unsigned i = 0; i < fig.nb_plots(); ++i)
    {
        gr::Plot p = fig[i];
        P.emplace_back(p.point().get_abscissa(), p.point().get_ordinate());
    }

    return P;
}
}

#endif //ALPHA_CONVEX_HULL_SETUP_H
