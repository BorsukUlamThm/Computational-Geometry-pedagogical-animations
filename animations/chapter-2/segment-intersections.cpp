#include "segment_intersections_events.h"
#include "segment_intersections_utils.h"
#include "geometry/utils/point_comparisons.h"


namespace chap2_segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace segment_intersections_utils;
	using namespace segment_intersections_events;


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
			auto x1 = boost::rational_cast<gr::Coordinate>(s.p1.x);
			auto y1 = boost::rational_cast<gr::Coordinate>(s.p1.y);
			auto x2 = boost::rational_cast<gr::Coordinate>(s.p2.x);
			auto y2 = boost::rational_cast<gr::Coordinate>(s.p2.y);

			animation[SEGMENTS].add_segment(x1, y1, x2, y2);
		}

		animation.make_new_frame();
	}

	void compute_intersections(segment_set& S,
							   gr::Animation& animation)
	{
		clean_segment_set(S);
		make_first_frame(S, animation);

		tree_cmp comp(S);
		tree T(comp);
		queue Q (S, animation, T);

		Q.handle_events();
	}
}

int main(int argc, char** argv)
{
	using namespace chap2_segment_intersections;

	Options opt = process_command_line(argc, argv);
	segment_set S = make_segment_set(opt);

	std::vector<geo::Segment_2<int>> tmp;
	for (auto& s : S)
	{
		auto x1 = boost::rational_cast<int>(s.p1.x);
		auto y1 = boost::rational_cast<int>(s.p1.y);
		auto x2 = boost::rational_cast<int>(s.p2.x);
		auto y2 = boost::rational_cast<int>(s.p2.y);
		tmp.emplace_back(x1, y1, x2, y2);
	}

	geo::save_segment_2_set("log/chapter-2/segment_intersections", tmp);
	gr::Animation animation(NB_FIGURES);
	compute_intersections(S, animation);

	gr::Display_canvas canvas;
	canvas.set_title("Segment intersections - animation");
	canvas.run_animation(animation);

	return 0;
}