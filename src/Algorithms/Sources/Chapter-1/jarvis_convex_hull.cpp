#include "Graphics/View/View.h"
#include "Algorithms/Model/Model.h"
#include "Algorithms/Tools/Point_comparisons.h"


namespace chap1_jarvis_convex_hull
{
typedef alg::Point_2<int> point;
typedef alg::Polygon_2<int> convex_hull;
typedef std::vector<point> point_set;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_hull;
gr::Figure fig_line;


point_set make_point_set()
{
    gr::Acquisition_canvas canvas;
    canvas.add_point_acquisition();
    gr::Figure fig = canvas.acquire_buffer();

    point_set P;
    for(unsigned i = 0; i < fig.nb_plots(); ++i)
    {
        gr::Plot p = fig[i];
        P.emplace_back(p.point().get_abscissa(), p.point().get_ordinate());
    }

    return P;
}

point first_point(const point_set& P)
{
    point p = P[0];
    for(auto& q : P)
    {
        if(alg::point_left_point(q, p))
        {
            p = q;
        }
    }

    return p;
}

point next_point(const convex_hull& CH, const point_set& P)
{
    point last = CH[CH.size() - 1];
    unsigned i = 0;
    point p = P[i];
    while(p == last)
    {
        i++;
        p = P[i];
    }
    fig_hull.add_segment(last.x, last.y, p.x, p.y, sf::Color::Blue);
    slides.add_slide(fig_points, fig_hull);

    for(unsigned j = i + 1; j < P.size(); ++j)
    {
        if(P[j] == last || P[j] == p)
        {
            continue;
        }

        if(alg::point_left_line(P[j], last, p))
        {
            fig_points.add_segment(last.x, last.y, P[j].x, P[j].y, sf::Color::Red);
            slides.add_slide(fig_points, fig_hull);
            fig_hull.erase_last_plot();
            fig_hull.add_segment(last.x, last.y, P[j].x, P[j].y, sf::Color::Blue);

            p = P[j];
        }
        else
        {
            fig_points.add_segment(last.x, last.y, P[j].x, P[j].y, sf::Color::Green);
            slides.add_slide(fig_points, fig_hull);
        }
        fig_points.erase_last_plot();
    }

    return p;
}

void jarvis_convex_hull(const point_set& P)
{
    for(auto p : P)
    {
        fig_points.add_point(p.x, p.y);
    }
    slides.add_slide(fig_points);

    convex_hull CH;
    CH.push_back(first_point(P));
    CH.push_back(next_point(CH, P));
    fig_hull.add_segment(CH[0].x, CH[0].y,
                         CH[1].x, CH[1].y, sf::Color::Blue);
    slides.add_slide(fig_points, fig_hull);

    while(CH[CH.size() - 1] != CH[0])
    {
        point p = next_point(CH, P);
        point q = CH[CH.size() - 1];
        fig_hull.add_segment(p.x, p.y, q.x, q.y, sf::Color::Blue);
        slides.add_slide(fig_points, fig_hull);
        CH.push_back(p);
    }
    CH.vertices.pop_back();

    gr::Polygon_plt plot_CH(sf::Color::Blue);
    for(auto& v : CH.vertices)
    {
        plot_CH.add_vertex(v.x, v.y);
    }
    fig_hull.clear();
    fig_hull.add_polygon(plot_CH);
    slides.add_slide(fig_points, fig_hull);
}
}

int main()
{
    using namespace chap1_jarvis_convex_hull;

    point_set P = make_point_set();
    jarvis_convex_hull(P);

    gr::Display_canvas canvas;
    canvas.display_slide_show(slides);

    return 0;
}