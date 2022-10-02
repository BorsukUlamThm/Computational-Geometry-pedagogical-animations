#include "include/segment_intersections/si_events.h"
#include "include/segment_intersections/si_tree.h"
#include "include/segment_intersections/si_utils.h"
#include "geometry/utils/point_comparisons.h"


namespace chap2_segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace segment_intersections;


	void clean_segment_set(segment_set& S)
	{
		for (auto& s : S)
		{
			if (geo::point_above_point(s.p2, s.p1))
			{
				point tmp = s.p1;
				s.p1 = s.p2;
				s.p2 = tmp;
			}
		}
	}

	void make_first_frame(segment_set& S,
						  gr::Animation& animation)
	{
		for (auto& s : S)
		{
			gr::Coordinate x1(s.p1.x);
			gr::Coordinate y1(s.p1.y);
			gr::Coordinate x2(s.p2.x);
			gr::Coordinate y2(s.p2.y);

			animation[SEGMENTS].add_segment(x1, y1, x2, y2);
		}

		animation.make_new_frame();
	}

	void compute_intersections(segment_set& S,
							   gr::Animation& animation)
	{
		clean_segment_set(S);
		make_first_frame(S, animation);

		tree T(S);
		queue Q(S, animation, T);

		Q.handle_events();

		animation[EVENT].clear();
		animation[TREE].clear();
		animation.make_new_frame();
	}
}

int main(int argc, char** argv)
{
	using namespace chap2_segment_intersections;

	Options opt = process_command_line(argc, argv);
	segment_set S = make_segment_set(opt);

	geo::save_segment_2_set("log/chapter-2/segment_intersections", S);
	gr::Animation animation(NB_FIGURES);
	compute_intersections(S, animation);

	gr::Animation_canvas canvas;
	canvas.set_title("Segment intersections - animation");
	canvas.run_animation(animation);

	return 0;
}