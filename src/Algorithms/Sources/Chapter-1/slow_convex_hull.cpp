#include "Graphics/View/View.h"
#include "Algorithms/Model/Point_2.h"
#include "Algorithms/Model/Segment_2.h"
#include "Algorithms/Model/Polygon_2.h"
#include "Algorithms/Tools/Point_comparisons.h"


namespace chap1_slow_convex_hull
{
typedef alg::Point_2<int> point;
typedef alg::Segment_2<int> segment;
typedef alg::Polygon_2<int> convex_hull;
typedef std::vector<point> point_set;
typedef std::vector<segment> segment_set;

gr::Slide_show slides;
gr::Figure fig_points;
gr::Figure fig_outside_segments;


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

            fig_outside_segments.add_segment(P[i].x, P[i].y, P[j].x, P[j].y);

            bool is_ok = true;
            for(unsigned k = 0; k < n; ++k)
            {
                if(alg::point_left_line(P[k], P[i], P[j]))
                {
                    is_ok = false;
                }
            }
            if(is_ok)
            {
                E.emplace_back(P[i], P[j]);
            }
        }
    }
    return E;
}

void slow_convex_hull(const point_set& P)
{
    for(auto p : P)
    {
        fig_points.add_point(p.x, p.y);
    }
    slides.add_slide(fig_points);

    segment_set E = make_outside_segments(P);
}
}

int main()
{
    using namespace chap1_slow_convex_hull;

    point_set S;
    S.push_back(point(0, 0));
    S.push_back(point(10, 0));
    S.push_back(point(0, 10));
    S.push_back(point(10, 10));
    S.push_back(point(5, 5));

    slow_convex_hull(S);
    gr::Canvas canvas;
    canvas.display_slide_show(slides);

    return 0;
}