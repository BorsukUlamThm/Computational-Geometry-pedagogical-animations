#include "include/utils.h"
#include "graphics/view/Animation_canvas.h"
#include "geometry/utils/point_comparisons.h"


namespace chap1_rotating_convex_hull
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace convex_hull_utils;

	enum Figures
	{
		POINTS,
		HULL,
		LINE,
		TEXT,
		NB_FIGURES
	};


	struct rotation_order
	{
		point leftmost_point;

		explicit rotation_order(const point_set& P)
		{
			leftmost_point = P[0];
			for (auto& p : P)
			{
				if (geo::point_left_point(p, leftmost_point))
				{
					leftmost_point = p;
				}
			}
		}

		bool operator()(const point& p,
						const point& q) const
		{
			if (p == q)
			{
				return true;
			}
			if (p == leftmost_point)
			{
				return true;
			}
			if (q == leftmost_point)
			{
				return false;
			}

			return geo::point_left_line(q, leftmost_point, p);
		}
	};

	bool right_turn(const convex_hull& hull,
					const point& p)
	{
		if (hull.size() < 2)
		{
			return false;
		}

		unsigned n = hull.size();
		return geo::point_right_line(p, hull[n - 2], hull[n - 1]);
	}

	convex_hull make_hull(const point_set& P,
						  gr::Animation& animation)
	{
		gr::Coordinate P0_x(P[0].x);
		gr::Coordinate P0_y(P[0].y);
		gr::Coordinate P1_x(P[1].x);
		gr::Coordinate P1_y(P[1].y);

		unsigned n = P.size();
		animation[LINE].add_vertical_line(P0_x);
		animation.make_new_frame(POINTS, HULL);

		convex_hull CH;
		CH.push_back(P[0]);
		CH.push_back(P[1]);

		animation[HULL].add_segment(P0_x, P0_y,
									P1_x, P1_y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_line(P0_x, P0_y, P1_x, P1_y);
		animation.make_new_frame(POINTS, HULL, LINE);

		for (unsigned i = 2; i < n; ++i)
		{
			unsigned k = CH.size();
			gr::Coordinate CHk1_x(CH[k - 1].x);
			gr::Coordinate CHk1_y(CH[k - 1].y);
			gr::Coordinate CHk2_x(CH[k - 2].x);
			gr::Coordinate CHk2_y(CH[k - 2].y);
			gr::Coordinate Pi_x(P[i].x);
			gr::Coordinate Pi_y(P[i].y);

			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(CHk2_x, CHk2_y,
										CHk1_x, CHk1_y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_line(P0_x, P0_y, Pi_x, Pi_y);

			while (right_turn(CH, P[i]))
			{
				gr::Coordinate back_x(CH.back().x);
				gr::Coordinate back_y(CH.back().y);

				animation[HULL].add_segment(back_x, back_y,
											Pi_x, Pi_y, gr::RED);
				gr::Point_shp point_shp(back_x, back_y);
				animation[TEXT].add_text("deleted", point_shp, 16, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				CH.pop_back();
			}
			gr::Coordinate back_x(CH.back().x);
			gr::Coordinate back_y(CH.back().y);

			gr::Point_shp point_shp(back_x, back_y);
			animation[TEXT].add_text("ok", point_shp, 16, gr::GREEN);
			animation[HULL].add_segment(back_x, back_y,
										Pi_x, Pi_y, gr::GREEN);
			CH.push_back(P[i]);
			animation.make_new_frame();
			animation[TEXT].clear();
		}

		unsigned k = CH.size();
		gr::Coordinate CHk1_x(CH[k - 1].x);
		gr::Coordinate CHk1_y(CH[k - 1].y);
		gr::Coordinate CHk2_x(CH[k - 2].x);
		gr::Coordinate CHk2_y(CH[k - 2].y);

		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(CHk2_x, CHk2_y,
									CHk1_x, CHk1_y, gr::YELLOW);

		return CH;
	}

	void make_convex_hull(point_set& P,
						  gr::Animation& animation)
	{
		for (auto& p : P)
		{
			gr::Coordinate x(p.x);
			gr::Coordinate y(p.y);
			animation[POINTS].add_point(x, y);
		}
		animation.make_new_frame(POINTS, HULL);
		rotation_order order(P);
		std::sort(P.begin(), P.end(), order);

		convex_hull CH = make_hull(P, animation);

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
	using namespace chap1_rotating_convex_hull;

	Options opt = process_command_line(argc, argv);
	point_set P = make_point_set(opt);

	geo::save_point_2_set("log/chapter-1/rotating_convex_hull", P);
	gr::Animation animation(NB_FIGURES);
	make_convex_hull(P, animation);

	gr::Animation_canvas canvas;
	canvas.set_title("Rotating convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}