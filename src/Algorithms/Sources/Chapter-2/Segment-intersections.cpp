#include "Segment_intersections/Segment_intersections_setup.h"
#include "Segment_intersections/Segment_intersections_events.h"


namespace chap2_segment_intersections
{
gr::Slide_show slides;
gr::Figure fig_segments;
gr::Figure fig_line;


void clean_segment_set(segment_set& S)
{
    for(auto& s : S)
    {
        if(alg::point_above_point(s.dst, s.ogn))
        {
            point tmp = s.ogn;
            s.ogn = s.dst;
            s.dst = tmp;
        }
    }
}

void compute_intersections(segment_set& S)
{
    clean_segment_set(S);

    for(auto& s : S)
    {
        auto x1 = boost::rational_cast<float>(s.ogn.x);
        auto y1 = boost::rational_cast<float>(s.ogn.y);
        auto x2 = boost::rational_cast<float>(s.dst.x);
        auto y2 = boost::rational_cast<float>(s.dst.y);
        fig_segments.add_segment(x1, y1, x2, y2);
    }
    slides.add_slide(fig_segments);

    Event_queue Q;
    for(unsigned i = 0; i < S.size(); ++i)
    {
        Q.insert_upper_point(S[i].ogn, i);
        Q.insert_lower_point(S[i].dst, i);
    }

    Q.handle_events();
}
}

int main(int argc, char** argv)
{
    using namespace chap2_segment_intersections;

    Segment_intersections_options opt = process_command_line(argc, argv);
    segment_set S = make_segment_set(opt);

    std::vector<alg::Segment_2<int>> tmp;
    for(auto& s : S)
    {
        auto x1 = boost::rational_cast<int>(s.ogn.x);
        auto y1 = boost::rational_cast<int>(s.ogn.y);
        auto x2 = boost::rational_cast<int>(s.dst.x);
        auto y2 = boost::rational_cast<int>(s.dst.y);
        tmp.emplace_back(x1, y1, x2, y2);
    }

    alg::save_segment_2_set("log/Chapter-2/segment_intersections", tmp);
    compute_intersections(S);

    gr::Display_canvas canvas;
    canvas.set_title("Segment intersections - animation");
    canvas.display_slide_show(slides);

    return 0;
}