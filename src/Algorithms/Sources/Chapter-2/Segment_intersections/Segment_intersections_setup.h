#ifndef ALPHA_SEGMENT_INTERSECTIONS_SETUP_H
#define ALPHA_SEGMENT_INTERSECTIONS_SETUP_H

#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>


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
    Input_type input_type = RANDOM;
    unsigned nb_random_segments = 50;
    unsigned long seed = time_seed;
    std::string input_path;
};


segment_set make_segment_set(const Segment_intersections_options& opt)
{
    std::cout << "initializing " << opt.nb_random_segments << " random points"
              << std::endl << "seed : " << opt.seed << std::endl;

    alg::Normal_number_generator<int> ng(opt.seed);
    auto tmp = alg::random_segment_2_set<int>(opt.nb_random_segments, ng);

    segment_set S;
    for(auto & s : tmp)
    {
        S.emplace_back(s.ogn.x, s.ogn.y, s.dst.x, s.dst.y);
    }

    return S;
}
}

#endif //ALPHA_SEGMENT_INTERSECTIONS_SETUP_H
