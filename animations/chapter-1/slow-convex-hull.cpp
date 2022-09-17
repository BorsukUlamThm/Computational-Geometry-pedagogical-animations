#include "include/convex_hull_utils.h"
#include "graphics/view/Display_canvas.h"
#include "geometry/utils/point_comparisons.h"


namespace chap1_slow_convex_hull
{
	namespace gr = graphics;
	namespace geo = geometry;

	using namespace convex_hull_utils;
	typedef geo::Segment_2<int> segment;
	typedef std::vector<segment> segment_set;

	enum Figures
	{
		POINTS,
		OUTSIDE_SEGMENTS,
		CONVEX_HULL,
		NB_FIGURES
	};


	segment_set make_outside_segments(const point_set& P,
									  gr::Animation& animation)
	{
		unsigned n = P.size();
		segment_set E;
		for (unsigned i = 0; i < n; ++i)
		{
			for (unsigned j = 0; j < n; ++j)
			{
				if (i == j)
					continue;

				animation[OUTSIDE_SEGMENTS].add_vector(
						P[i].x, P[i].y, P[j].x, P[j].y, gr::YELLOW);
				animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);

				bool is_ok = true;
				for (unsigned k = 0; k < n; ++k)
				{
					if (geo::point_strictly_left_line(P[k], P[i], P[j]))
					{
						is_ok = false;
						animation[POINTS].add_point(P[k].x, P[k].y, gr::RED,
													20);
						animation[OUTSIDE_SEGMENTS].add_vector(
								P[i].x, P[i].y, P[j].x, P[j].y, gr::RED);
						animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
						animation[POINTS].erase_last_shape();
						animation[OUTSIDE_SEGMENTS].erase_last_shape();
						break;
					}
					else
					{
						animation[POINTS].add_point(P[k].x, P[k].y, gr::GREEN,
													7);
						animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
						animation[POINTS].erase_last_shape();
					}
				}
				animation[OUTSIDE_SEGMENTS].erase_last_shape();
				if (is_ok)
				{
					E.emplace_back(P[i], P[j]);
					animation[OUTSIDE_SEGMENTS].add_vector(
							P[i].x, P[i].y, P[j].x, P[j].y, gr::GREEN);
					animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
				}
			}
		}

		animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
		for (unsigned i = 0; i < E.size(); ++i)
		{
			gr::Segment_obj s(E[i].p1.x, E[i].p1.y, E[i].p2.x, E[i].p2.y);
			animation[OUTSIDE_SEGMENTS].add_text(std::to_string(i), s);
		}
		animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
		animation[OUTSIDE_SEGMENTS].erase_last_k_shapes(E.size());

		return E;
	}

	convex_hull sort_outside_segment(segment_set& E,
									 gr::Animation& animation)
	{
		convex_hull CH;
		segment s = E[0];
		CH.push_back(s.p1);

		animation[OUTSIDE_SEGMENTS].clear();
		animation[OUTSIDE_SEGMENTS].add_vector(
				s.p1.x, s.p1.y, s.p2.x, s.p2.y, gr::YELLOW);
		animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);

		while (CH.size() < E.size())
		{
			for (auto& e : E)
			{
				if (e.p1 == s.p2)
				{
					CH.push_back(s.p2);
					s = e;

					animation[OUTSIDE_SEGMENTS].add_vector(
							e.p1.x, e.p1.y, e.p2.x, e.p2.y, gr::GREEN);
					animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
					animation[OUTSIDE_SEGMENTS].erase_last_shape();
					break;
				}
				else
				{
					animation[OUTSIDE_SEGMENTS].add_vector(
							e.p1.x, e.p1.y, e.p2.x, e.p2.y, gr::RED);
					animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
					animation[OUTSIDE_SEGMENTS].erase_last_shape();
				}
			}
			animation[OUTSIDE_SEGMENTS].add_vector(
					s.p1.x, s.p1.y, s.p2.x, s.p2.y, gr::YELLOW);
			animation.make_new_frame(POINTS, OUTSIDE_SEGMENTS);
		}

		return CH;
	}

	void slow_convex_hull(const point_set& P,
						  gr::Animation& animation)
	{
		for (auto p : P)
		{
			animation[POINTS].add_point(p.x, p.y);
		}
		animation.make_new_frame(POINTS);

		segment_set E = make_outside_segments(P, animation);
		convex_hull CH = sort_outside_segment(E, animation);

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& v : CH)
		{
			plot_CH.add_vertex(v.x, v.y);
		}
		animation[CONVEX_HULL].add_polygon(plot_CH);
		animation.make_new_frame(POINTS, CONVEX_HULL);
	}
}

int main(int argc, char** argv)
{
	using namespace convex_hull_utils;
	using namespace chap1_slow_convex_hull;

	Options opt = process_command_line(argc, argv);
	point_set P = make_point_set(opt);

	geo::save_point_2_set("log/chapter-1/slow_convex_hull", P);
	gr::Animation animation(NB_FIGURES);
	slow_convex_hull(P, animation);

	gr::Display_canvas canvas;
	canvas.set_title("Slow convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}