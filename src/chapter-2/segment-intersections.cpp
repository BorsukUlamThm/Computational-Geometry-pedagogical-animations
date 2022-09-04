#include "segment_intersections_events.h"
#include "segment_intersections_setup.h"
#include "geometry/utils/Event_queue.h"


namespace chap2_segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	gr::Animation animation(NB_FIGURES);


	void clean_segment_set(segment_set& S)
	{
		for(auto& s : S)
		{
			if(geo::point_above_point(s.p2, s.p1))
			{
				point tmp = s.p1;
				s.p1 = s.p2;
				s.p2 = tmp;
			}
		}
	}

	void compute_intersections(segment_set& S)
	{
		clean_segment_set(S);

		for(auto& s : S)
		{
			auto x1 = boost::rational_cast<float>(s.p1.x);
			auto y1 = boost::rational_cast<float>(s.p1.y);
			auto x2 = boost::rational_cast<float>(s.p2.x);
			auto y2 = boost::rational_cast<float>(s.p2.y);
			animation[SEGMENTS].add_segment(x1, y1, x2, y2);
		}
		animation.make_new_frame(SEGMENTS);

		Event_queue Q;
		for(unsigned i = 0; i < S.size(); ++i)
		{
			Q.insert_upper_point(S[i].p1, i);
			Q.insert_lower_point(S[i].p2, i);
		}

		Q.handle_events();
	}
}

int main(int argc, char** argv)
{
	using namespace chap2_segment_intersections;

	Segment_intersections_options opt = process_command_line(argc, argv);
	segment_set S = make_segment_set(opt);

	std::vector<geo::Segment_2<int>> tmp;
	for(auto& s : S)
	{
		auto x1 = boost::rational_cast<int>(s.p1.x);
		auto y1 = boost::rational_cast<int>(s.p1.y);
		auto x2 = boost::rational_cast<int>(s.p2.x);
		auto y2 = boost::rational_cast<int>(s.p2.y);
		tmp.emplace_back(x1, y1, x2, y2);
	}

	geo::save_segment_2_set("log/Chapter-2/segment_intersections", tmp);
	compute_intersections(S);

	gr::Display_canvas canvas;
	canvas.set_title("Segment intersections - animation");
	canvas.run_animation(animation);

	return 0;
}