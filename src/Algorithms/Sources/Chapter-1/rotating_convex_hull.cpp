#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"


namespace chap1_rotating_convex_hull
{
typedef alg::Point_2<int> point;
typedef std::vector<point> convex_hull;
typedef std::vector<point> point_set;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_hull;
gr::Figure fig_line;


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
        return alg::random_point_2_set<int>(nb_random_points, ng);
    }

    gr::Acquisition_canvas canvas;
    canvas.set_title("Rotating convex hull - acquisition");
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

struct Rotation_order
{
    point leftmost_point;

    Rotation_order(const point_set& P)
    {
        leftmost_point = P[0];
        for(auto& p : P)
        {
            if(alg::point_left_point(p, leftmost_point))
            {
                leftmost_point = p;
            }
        }
    }

    bool operator()(const point& p, const point& q) const
    {
        if(p == q)
        {
            return true;
        }
        if(p == leftmost_point)
        {
            return true;
        }
        if(q == leftmost_point)
        {
            return false;
        }

        return alg::point_left_line(q, leftmost_point, p);
    }
};

bool right_turn(const convex_hull& hull, const point& p)
{
    if(hull.size() < 2)
    {
        return false;
    }

    unsigned n = hull.size();
    return alg::point_right_line(p, hull[n - 2], hull[n - 1]);
}

convex_hull make_hull(const point_set& P)
{
    unsigned n = P.size();
    fig_line.add_vertical_line(P[0].x);
    slides.add_slide(fig_points, fig_line);

    convex_hull CH;
    CH.push_back(P[0]);
    CH.push_back(P[1]);

    fig_hull.add_segment(P[0].x, P[0].y,
                         P[1].x, P[1].y, gr::YELLOW);
    fig_line.clear();
    fig_line.add_line(P[0].x, P[0].y, P[1].x, P[1].y);
    slides.add_slide(fig_points, fig_line, fig_hull);

    for(unsigned i = 2; i < n; ++i)
    {
        unsigned k = CH.size();
        fig_hull.erase_last_plot();
        fig_hull.add_segment(CH[k - 2].x, CH[k - 2].y,
                             CH[k - 1].x, CH[k - 1].y, gr::YELLOW);
        fig_line.clear();
        fig_line.add_line(P[0].x, P[0].y, P[i].x, P[i].y);

        while(right_turn(CH, P[i]))
        {
            fig_hull.add_segment(CH.back().x, CH.back().y,
                                 P[i].x, P[i].y, gr::RED);
            slides.add_slide(fig_points, fig_line, fig_hull);
            fig_hull.erase_last_k_plots(2);
            CH.pop_back();
        }
        fig_hull.add_segment(CH.back().x, CH.back().y,
                             P[i].x, P[i].y, gr::GREEN);
        CH.push_back(P[i]);
        slides.add_slide(fig_points, fig_line, fig_hull);
    }

    unsigned k = CH.size();
    fig_hull.erase_last_plot();
    fig_hull.add_segment(CH[k - 2].x, CH[k - 2].y,
                         CH[k - 1].x, CH[k - 1].y, gr::YELLOW);

    return CH;
}

void make_convex_hull(point_set& P)
{
    for(auto p : P)
    {
        fig_points.add_point(p.x, p.y);
    }
    slides.add_slide(fig_points);

    Rotation_order order(P);
    std::sort(P.begin(), P.end(), order);

    convex_hull CH = make_hull(P);

    gr::Polygon_plt plot_CH(gr::YELLOW);
    for(auto& v : CH)
    {
        plot_CH.add_vertex(v.x, v.y);
    }
    fig_hull.clear();
    fig_hull.add_polygon(plot_CH);
    slides.add_slide(fig_points, fig_hull);
}
}

int main(int argc, char** argv)
{
    using namespace chap1_rotating_convex_hull;

    process_command_line(argc, argv);
    point_set P = make_point_set();
    make_convex_hull(P);

    gr::Display_canvas canvas;
    canvas.set_title("Convex hull - animation");
    canvas.display_slide_show(slides);

    return 0;
}