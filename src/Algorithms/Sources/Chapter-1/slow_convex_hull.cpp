#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"


namespace chap1_slow_convex_hull
{
typedef alg::Point_2<int> point;
typedef alg::Segment_2<int> segment;
typedef std::vector<point> convex_hull;
typedef std::vector<point> point_set;
typedef std::vector<segment> segment_set;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_outside_segments;
gr::Figure fig_convex_hull;


bool acquire_points = false;
bool random_input = true;
unsigned nb_random_points = 50;
unsigned long seed = time_seed;

void process_command_line(int argc, char** argv)
{
    for(unsigned i = 0; i < argc; ++i)
    {
        if(std::string(argv[i]) == "-a")
        {
            acquire_points = true;
            random_input = false;
            continue;
        }
        if(std::string(argv[i]) == "-r")
        {
            random_input = true;
            acquire_points = false;
            ++i;
            if(i >= argc)
            {
                std::cerr << "invalid -r parameter, missing"
                          << " number of random points"
                          << std::endl;
                continue;
            }
            nb_random_points = std::stoi(std::string(argv[i]));
        }
        if(std::string(argv[i]) == "-s")
        {
            ++i;
            if(i >= argc)
            {
                std::cerr << "invalid -s parameter, missing seed"
                          << std::endl;
                continue;
            }
            seed = std::stoi(std::string(argv[i]));
        }
    }
}

point_set make_point_set()
{
    if(random_input)
    {
        std::cout << "initializing " << nb_random_points << " random points"
                  << std::endl << "seed : " << seed << std::endl;

        alg::Normal_number_generator<int> ng(seed);
        return alg::random_2D_point_set<int>(nb_random_points, ng);
    }

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

segment_set make_outside_segments(const point_set& P)
{
    unsigned n = P.size();
    segment_set E;
    for(unsigned i = 0; i < n; ++i)
    {
        for(unsigned j = 0; j < n; ++j)
        {
            if(i == j)
                continue;

            fig_outside_segments.add_vector(
                    P[i].x, P[i].y, P[j].x, P[j].y, sf::Color::Blue);
            slides.add_slide(fig_points, fig_outside_segments);

            bool is_ok = true;
            for(unsigned k = 0; k < n; ++k)
            {
                if(alg::point_strictly_left_line(P[k], P[i], P[j]))
                {
                    is_ok = false;
                    fig_points.add_point(P[k].x, P[k].y, sf::Color::Red, 7);
                    fig_outside_segments.add_vector(
                            P[i].x, P[i].y, P[j].x, P[j].y, sf::Color::Red);
                    slides.add_slide(fig_points, fig_outside_segments);
                    fig_points.erase_last_plot();
                    fig_outside_segments.erase_last_plot();
                    break;
                }
                else
                {
                    fig_points.add_point(P[k].x, P[k].y, sf::Color::Green, 7);
                    slides.add_slide(fig_points, fig_outside_segments);
                    fig_points.erase_last_plot();
                }
            }
            fig_outside_segments.erase_last_plot();
            if(is_ok)
            {
                E.emplace_back(P[i], P[j]);
                fig_outside_segments.add_vector(
                        P[i].x, P[i].y, P[j].x, P[j].y, sf::Color::Green);
                slides.add_slide(fig_points, fig_outside_segments);
            }
        }
    }

    slides.add_slide(fig_points, fig_outside_segments);
    for(unsigned i = 0; i < E.size(); ++i)
    {
        gr::Vector_plt v (E[i].ogn.x, E[i].ogn.y, E[i].dst.x, E[i].dst.y);
        fig_outside_segments.add_text(std::to_string(i), v);
    }
    slides.add_slide(fig_points, fig_outside_segments);
//    fig_outside_segments.pop_last_n_plots(E.size());

    return E;
}

convex_hull sort_outside_segment(segment_set& E)
{
    convex_hull CH;
    segment s = E[0];
    CH.push_back(s.ogn);

    fig_outside_segments.clear();
    fig_outside_segments.add_vector(
            s.ogn.x, s.ogn.y, s.dst.x, s.dst.y, sf::Color::Blue);
    slides.add_slide(fig_points, fig_outside_segments);

    while(CH.size() < E.size())
    {
        for(auto & e : E)
        {
            if(e.ogn == s.dst)
            {
                CH.push_back(s.dst);
                s = e;

                fig_outside_segments.add_vector(
                        e.ogn.x, e.ogn.y, e.dst.x, e.dst.y, sf::Color::Green);
                slides.add_slide(fig_points, fig_outside_segments);
                fig_outside_segments.erase_last_plot();
                break;
            }
            else
            {
                fig_outside_segments.add_vector(
                        e.ogn.x, e.ogn.y, e.dst.x, e.dst.y, sf::Color::Red);
                slides.add_slide(fig_points, fig_outside_segments);
                fig_outside_segments.erase_last_plot();
            }
        }
        fig_outside_segments.add_vector(
                s.ogn.x, s.ogn.y, s.dst.x, s.dst.y, sf::Color::Blue);
        slides.add_slide(fig_points, fig_outside_segments);
    }

    return CH;
}

void slow_convex_hull(const point_set& P)
{
    for(auto p : P)
    {
        fig_points.add_point(p.x, p.y);
    }
    slides.add_slide(fig_points);

    segment_set E = make_outside_segments(P);
    convex_hull CH = sort_outside_segment(E);

    gr::Polygon_plt plot_CH(sf::Color::Blue);
    for(auto& v : CH)
    {
        plot_CH.add_vertex(v.x, v.y);
    }
    fig_convex_hull.add_polygon(plot_CH);
    slides.add_slide(fig_points, fig_convex_hull);
}
}

int main(int argc, char** argv)
{
    using namespace chap1_slow_convex_hull;

    process_command_line(argc, argv);
    point_set P = make_point_set();
    slow_convex_hull(P);

    gr::Display_canvas canvas;
    canvas.display_slide_show(slides);

    return 0;
}