#pragma once

/** @cond */
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
/** @endcond */
#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"


namespace chap2_segment_intersections
{
typedef boost::rational<boost::multiprecision::cpp_int> rational;
typedef alg::Point_2<rational> point;
typedef alg::Segment_2<rational> segment;
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
    std::string input_path;
};

Segment_intersections_options process_command_line(int argc, char** argv)
{
    Segment_intersections_options opt;

    for(unsigned i = 0; i < argc; ++i)
    {
        if(argv[i][0] != '-')
        {
            continue;
        }

        if(std::string(argv[i]) == "-a")
        {
            opt.input_type = ACQUISITION;
            continue;
        }
        if(std::string(argv[i]) == "-r")
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
                opt.nb_random_segments = std::stoi(std::string(argv[i]));
            }
            catch(const std::invalid_argument& ia)
            {
                std::cerr << "invalid -r parameter, missing"
                          << " number of random points"
                          << std::endl;
                --i;
            }
        }

        if(std::string(argv[i]) == "-s")
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

        if(std::string(argv[i]) == "-i")
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
            std::cerr << "unknown " << argv[i] << " option ignored" << std::endl;
        }
    }

    return opt;
}


segment_set make_segment_set(const Segment_intersections_options& opt)
{
    if (opt.input_type == RANDOM)
    {
        std::cout << "initializing " << opt.nb_random_segments << " random points"
                  << std::endl << "seed : " << opt.seed << std::endl;

        alg::Normal_number_generator<int> ng(opt.seed);
        auto tmp = alg::random_segment_2_set < int > (opt.nb_random_segments, ng);

        segment_set S;
        for (auto& s : tmp)
        {
            S.emplace_back(s.ogn.x, s.ogn.y, s.dst.x, s.dst.y);
        }

        return S;
    }

    auto tmp = alg::read_segment_2_set<int>(opt.input_path);
    segment_set S;
    for(auto& s : tmp)
    {
        S.emplace_back(s.ogn.x, s.ogn.y, s.dst.x, s.dst.y);
    }
    return S;
}
}