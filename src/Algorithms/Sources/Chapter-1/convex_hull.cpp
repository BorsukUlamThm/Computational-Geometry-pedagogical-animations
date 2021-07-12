#include "Graphics/View/View.h"
#include "Algorithms/Model/Model.h"
#include "Algorithms/Tools/Point_comparisons.h"


namespace chap1_convex_hull
{
typedef alg::Point_2<int> point;
typedef std::vector<point> convex_hull;
typedef std::vector<point> point_set;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_hull;


point_set make_point_set()
{
    gr::Acquisition_canvas canvas;
    canvas.add_point_acquisition();
    gr::Figure fig = canvas.acquire_buffer();

    point_set S;
    for(unsigned i = 0; i < fig.nb_plots(); ++i)
    {
        gr::Plot p = fig[i];
        S.emplace_back(p.point().get_abscissa(), p.point().get_ordinate());
    }
    return S;
}


bool left_turn(const convex_hull& hull, const point& p)
{
    if(hull.size() < 2)
    {
        return false;
    }

    unsigned n = hull.size();
    return alg::point_left_line(p, hull[n - 1], hull[n - 2]);
}

convex_hull make_upper_hull(const point_set& P)
{
    unsigned n = P.size();
    convex_hull U;
    U.push_back(P[0]);
    U.push_back(P[1]);

    for(unsigned i = 2; i < n; ++i)
    {
        while(left_turn(U, P[i]))
        {
            U.pop_back();
        }
        U.push_back(P[i]);
    }

    return U;
}

convex_hull make_lower_hull(const point_set& P)
{
    unsigned n = P.size();
    convex_hull L;
    L.push_back(P[n - 1]);
    L.push_back(P[n - 2]);

    for(unsigned i = n - 3; i < n; --i)
    {
        while(left_turn(L, P[i]))
        {
            L.pop_back();
        }
        L.push_back(P[i]);
    }

    return L;
}

convex_hull make_convex_hull(point_set& P)
{
    std::sort(P.begin(), P.end(), alg::point_left_point<int>);

    convex_hull U = make_upper_hull(P);
    convex_hull L = make_lower_hull(P);

    U.pop_back();
    L.pop_back();

    for(auto& p : L)
    {
        U.push_back(p);
    }
    return U;
}
}

int main()
{
    using namespace chap1_convex_hull;

    point_set P = make_point_set();
    convex_hull CH = make_convex_hull(P);

    gr::Figure fig;
    for(auto& p : P)
    {
        fig.add_point(p.x, p.y);
    }

    gr::Polygon_plt plot_CH(sf::Color::Blue);
    for(auto& v : CH)
    {
        plot_CH.add_vertex(v.x, v.y);
    }
    fig.add_polygon(plot_CH);

    gr::Display_canvas canvas;
    canvas.display_figure(fig);

    return 0;
}