#include "include/utils.h"
#include "graphics/view/Display_canvas.h"
#include "geometry/utils/point_comparisons.h"


namespace chap1_jarvis_convex_hull
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace convex_hull_utils;

	enum Figures
	{
		POINTS,
		HULL,
		NB_FIGURES
	};


	point first_point(const point_set& P)
	{
		point p = P[0];
		for (auto& q : P)
		{
			if (geo::point_left_point(q, p))
			{
				p = q;
			}
		}

		return p;
	}

	point next_point(const convex_hull& CH,
					 const point_set& P,
					 gr::Animation& animation)
	{
		point last = CH[CH.size() - 1];
		unsigned i = 0;
		point p = P[i];
		gr::Coordinate last_x(last.x);
		gr::Coordinate last_y(last.y);
		gr::Coordinate p_x(p.x);
		gr::Coordinate p_y(p.y);

		while (p == last)
		{
			i++;
			p = P[i];
		}
		animation[HULL].add_segment(last_x, last_y, p_x, p_y, gr::PURPLE);
		animation.make_new_frame(POINTS, HULL);

		for (unsigned j = i + 1; j < P.size(); ++j)
		{
			gr::Coordinate Pi_x(P[i].x);
			gr::Coordinate Pi_y(P[i].y);
			gr::Coordinate Pj_x(P[j].x);
			gr::Coordinate Pj_y(P[j].y);

			if (P[j] == last || P[j] == p)
			{ continue; }

			if (geo::point_left_line(P[j], last, p))
			{
				animation[POINTS].add_segment(last_x, last_y, Pj_x, Pj_y,
											  gr::RED);
				animation.make_new_frame(POINTS, HULL);
				animation[HULL].erase_last_shape();
				animation[HULL].add_segment(last_x, last_y, Pj_x, Pj_y,
											gr::PURPLE);

				p = P[j];
			}
			else
			{
				animation[POINTS].add_segment(last_x, last_y, Pj_x, Pj_y,
											  gr::GREEN);
				animation.make_new_frame(POINTS, HULL);
			}
			animation[POINTS].erase_last_shape();
		}

		return p;
	}

	void jarvis_convex_hull(const point_set& P,
							gr::Animation& animation)
	{
		for (auto p : P)
		{
			gr::Coordinate x(p.x);
			gr::Coordinate y(p.y);

			animation[POINTS].add_point(x, y);
		}
		animation.make_new_frame(POINTS);

		convex_hull CH;
		CH.push_back(first_point(P));
		CH.push_back(next_point(CH, P, animation));

		gr::Coordinate CH0_x(CH[0].x);
		gr::Coordinate CH0_y(CH[0].y);
		gr::Coordinate CH1_x(CH[1].x);
		gr::Coordinate CH1_y(CH[1].y);
		animation[HULL].add_segment(CH0_x, CH0_y,
									CH1_x, CH1_y, gr::YELLOW);
		animation.make_new_frame(POINTS, HULL);

		while (CH[CH.size() - 1] != CH[0])
		{
			point p = next_point(CH, P, animation);
			point q = CH[CH.size() - 1];

			gr::Coordinate px(p.x);
			gr::Coordinate py(p.y);
			gr::Coordinate qx(q.x);
			gr::Coordinate qy(q.y);

			animation[HULL].add_segment(px, py, qx, qy, gr::YELLOW);
			animation.make_new_frame(POINTS, HULL);
			CH.push_back(p);
		}
		CH.pop_back();

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& p : CH)
		{
			gr::Coordinate x(p.x);
			gr::Coordinate y(p.y);

			plot_CH.add_vertex(x, y);
		}
		animation[HULL].clear();
		animation[HULL].add_polygon(plot_CH);
		animation.make_new_frame(POINTS, HULL);
	}
}

int main(int argc, char** argv)
{
	using namespace convex_hull_utils;
	using namespace chap1_jarvis_convex_hull;

	Options opt = process_command_line(argc, argv);
	point_set P = make_point_set(opt);

	geo::save_point_2_set("log/chapter-1/jarvis_convex_hull", P);
	gr::Animation animation(NB_FIGURES);
	jarvis_convex_hull(P, animation);

	gr::Display_canvas canvas;
	canvas.set_title("Jarvis convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}