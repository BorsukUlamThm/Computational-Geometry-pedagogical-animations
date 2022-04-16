#ifndef ALPHA_SEGMENT_INTERSECTIONS_EVENTS_H
#define ALPHA_SEGMENT_INTERSECTIONS_EVENTS_H

#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>


namespace chap2_segment_intersections
{
typedef boost::rational<boost::multiprecision::cpp_int> rational;
typedef alg::Point_2<rational> point;
typedef alg::Segment_2<rational> segment;


struct Event
{
    point p;

    gr::Slide_show* slides;
    gr::Figure* fig_points;
    gr::Figure* fig_line;

    Event(const point& p,
          gr::Slide_show& slides,
          gr::Figure& fig_segments,
          gr::Figure& fig_line);

    void handle() const;
};

Event::Event(const point& p,
             gr::Slide_show& slides,
             gr::Figure& fig_segments,
             gr::Figure& fig_line):
             p(p),
             slides(&slides),
             fig_points(&fig_segments),
             fig_line(&fig_line)
{}

void Event::handle() const
{
    auto x = boost::rational_cast<float>(p.x);
    auto y = boost::rational_cast<float>(p.y);
    fig_points->add_point(x, y, gr::RED, 5);

    fig_line->clear();
    fig_line->add_horizontal_line(y);

    slides->add_slide(*fig_points, *fig_line);
    fig_points->erase_last_plot();
}

bool operator<(const Event& e1, const Event& e2)
{
    return alg::point_below_point(e1.p, e2.p);
}
}


#endif //ALPHA_SEGMENT_INTERSECTIONS_EVENTS_H
