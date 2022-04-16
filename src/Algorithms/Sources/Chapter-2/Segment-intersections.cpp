#include "Segment_intersections/Segment_intersections_setup.h"
#include "Segment_intersections/Segment_intersections_events.h"


namespace chap2_segment_intersections
{
typedef alg::Event_queue<Event> queue;

gr::Slide_show slides;
gr::Figure fig_segments;
gr::Figure fig_line;


void compute_intersections(const segment_set& S)
{
    for(auto& s : S)
    {
        auto x1 = boost::rational_cast<float>(s.ogn.x);
        auto y1 = boost::rational_cast<float>(s.ogn.y);
        auto x2 = boost::rational_cast<float>(s.dst.x);
        auto y2 = boost::rational_cast<float>(s.dst.y);
        fig_segments.add_segment(x1, y1, x2, y2);
    }
    slides.add_slide(fig_segments);

    queue Q;
    for(auto& s : S)
    {
        Event e1(s.ogn, slides, fig_segments, fig_line);
        Event e2(s.dst, slides, fig_segments, fig_line);

        Q.push_event(e1);
        Q.push_event(e2);
    }

    Q.handle_events();
}
}

int main(int argc, char** argv)
{
    using namespace chap2_segment_intersections;

    Segment_intersections_options opt;
    segment_set S = make_segment_set(opt);

    alg::save_segment_2_set("log/Chapter-2/segment_intersections", S);
    compute_intersections(S);

    gr::Display_canvas canvas;
    canvas.set_title("Segment intersections - animation");
    canvas.display_slide_show(slides);

    return 0;
}