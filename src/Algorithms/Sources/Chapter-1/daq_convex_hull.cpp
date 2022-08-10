/** @cond */
#include <list>
/** @endcond */
#include "Convex_hull_setup.h"


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

    gr::Polygon_shp plot_CH(gr::YELLOW);
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

    chs::Convex_hull_option opt = chs::process_command_line(argc, argv);
    point_set P = chs::make_point_set(opt);

    alg::save_point_2_set("log/Chapter-1/daq_convex_hull", P);
    daq_convex_hull(P);

    gr::Display_canvas canvas;
    canvas.set_title("Divide and conquer convex hull - animation");
    canvas.display_slide_show(slides);

    return 0;
}