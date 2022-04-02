#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <list>


namespace chap1_daq_convex_hull
{
typedef alg::Point_2<int> point;
typedef std::vector<point> point_set;
typedef std::list<point> half_hull;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_hull;
gr::Figure fig_half_hulls;
gr::Figure fig_turn;

void plot_turn(const half_hull& H, const half_hull::iterator it, gr::Color color)
{
    point p2 = *it;
    point p3 = *std::next(it);

    if(it == H.begin())
    {
        fig_turn.add_segment(p2.x, p2.y, p3.x, p3.y, color, color);
        return;
    }

    point p1 = *std::prev(it);

    fig_turn.add_segment(p1.x, p1.y, p2.x, p2.y, color, color);
    fig_turn.add_segment(p2.x, p2.y, p3.x, p3.y, color, color);
}

void plot_half_hull(const half_hull& H, gr::Color color = gr::PURPLE)
{
    if(H.size() == 1)
    {
        int x = H.begin()->x;
        int y = H.begin()->y;
        fig_half_hulls.add_point(x, y, color, 5);
    }


    auto it = H.begin();
    it++;

    for(;it != H.end(); ++it)
    {
        int x1 = (std::prev(it))->x;
        int y1 = (std::prev(it))->y;
        int x2 = it->x;
        int y2 = it->y;
        fig_half_hulls.add_segment(x1, y1, x2, y2, color, color);
    }
}


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
    canvas.set_title("Divide and conquer convex hull - acquisition");
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

/// returns true iff the three points prev(it), it, next(it) make a left turn
bool left_turn(const half_hull& H, half_hull::iterator it)
{
    if(it == H.begin())
    {
        return false;
    }

    auto prev = std::prev(it);
    auto next = std::next(it);
    return alg::point_left_line(*prev, *it, *next);
}

void make_convex(half_hull& H)
{
    auto it = std::next(H.begin());

    while(it != std::prev(H.end()))
    {
        while(left_turn(H, it))
        {
            plot_half_hull(H);
            plot_turn(H, it, gr::RED);
            slides.add_slide(fig_points, fig_half_hulls, fig_turn);
            fig_half_hulls.clear();
            fig_turn.clear();
            it = H.erase(it);
            --it;
        }
        plot_half_hull(H);
        plot_turn(H, it, gr::GREEN);
        slides.add_slide(fig_points, fig_half_hulls, fig_turn);
        fig_half_hulls.clear();
        fig_turn.clear();
        ++it;
    }
}

half_hull upper_merge(half_hull& UH1, half_hull& UH2)
{
    plot_half_hull(UH1);
    plot_half_hull(UH2);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    UH1.merge(UH2, alg::point_left_point<int>);
    plot_half_hull(UH1);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    make_convex(UH1);
    plot_half_hull(UH1, gr::YELLOW);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    return UH1;
}

half_hull lower_merge(half_hull& LH1, half_hull& LH2)
{
    plot_half_hull(LH1);
    plot_half_hull(LH2);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    LH1.merge(LH2, alg::point_right_point<int>);
    plot_half_hull(LH1);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    make_convex(LH1);
    plot_half_hull(LH1, gr::YELLOW);
    slides.add_slide(fig_points, fig_half_hulls);
    fig_half_hulls.clear();

    return LH1;
}

half_hull daq_upper_hull(const point_set& P, unsigned i, unsigned j)
{
    half_hull H;
    if(j - i == 0)
    {
        return H;
    }
    if(j - i == 1)
    {
        H.push_back(P[i]);
        return H;
    }

    half_hull UH1 = daq_upper_hull(P, i, (i + j) / 2);
    half_hull UH2 = daq_upper_hull(P, (i + j) / 2, j);

    return upper_merge(UH1, UH2);
}

half_hull daq_lower_hull(const point_set& P, unsigned i, unsigned j)
{
    half_hull H;
    if(j - i == 0)
    {
        return H;
    }
    if(j - i == 1)
    {
        H.push_back(P[i]);
        return H;
    }

    half_hull UH1 = daq_lower_hull(P, i, (i + j) / 2);
    half_hull UH2 = daq_lower_hull(P, (i + j) / 2, j);

    return lower_merge(UH1, UH2);
}

void daq_convex_hull(const point_set& P)
{
    for(auto p : P)
    {
        fig_points.add_point(p.x, p.y);
    }
    slides.add_slide(fig_points);

    unsigned n = P.size();
    half_hull U = daq_upper_hull(P, 0, n);
    half_hull L = daq_lower_hull(P, 0, n);

    U.pop_back();
    L.pop_back();
    U.splice(U.end(), L);

    gr::Polygon_plt plot_CH(gr::YELLOW);
    for(auto& v : U)
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
    using namespace chap1_daq_convex_hull;

    process_command_line(argc, argv);
    point_set P = make_point_set();
    daq_convex_hull(P);

    gr::Display_canvas canvas;
    canvas.set_title("Divide and conquer convex hull - animation");
    canvas.display_slide_show(slides);

    return 0;
}