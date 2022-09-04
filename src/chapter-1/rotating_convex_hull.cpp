#include "Convex_hull_setup.h"
#include "graphics/View/Display_canvas.h"
#include "geometry/Tools/Point_comparisons.h"


namespace chap1_rotating_convex_hull
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::Point_2<int> point;
	typedef std::vector<point> convex_hull;
	typedef std::vector<point> point_set;

	enum Figures
	{
		POINTS,
		HULL,
		LINE,
		TEXT,
		NB_FIGURES
	};


	struct Rotation_order
	{
		point leftmost_point;

		Rotation_order(const point_set& P)
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

		bool operator()(const point& p, const point& q) const
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
					const point& p,
					gr::Animation& animation)
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
		unsigned n = P.size();
		animation[LINE].add_vertical_line(P[0].x);
		animation.make_new_frame(POINTS, HULL);

		convex_hull CH;
		CH.push_back(P[0]);
		CH.push_back(P[1]);

		animation[HULL].add_segment(P[0].x, P[0].y,
									P[1].x, P[1].y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_line(P[0].x, P[0].y, P[1].x, P[1].y);
		animation.make_new_frame(POINTS, HULL, LINE);

		for (unsigned i = 2; i < n; ++i)
		{
			unsigned k = CH.size();
			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(CH[k - 2].x, CH[k - 2].y,
										CH[k - 1].x, CH[k - 1].y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_line(P[0].x, P[0].y, P[i].x, P[i].y);

			while (right_turn(CH, P[i], animation))
			{
				animation[HULL].add_segment(CH.back().x, CH.back().y,
											P[i].x, P[i].y, gr::RED);
				gr::Point_shp point_shp(CH.back().x, CH.back().y);
				animation[TEXT].add_text("deleted", point_shp, 16, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				CH.pop_back();
			}
			gr::Point_shp point_shp(CH.back().x, CH.back().y);
			animation[TEXT].add_text("ok", point_shp, 16, gr::GREEN);
			animation[HULL].add_segment(CH.back().x, CH.back().y,
										P[i].x, P[i].y, gr::GREEN);
			CH.push_back(P[i]);
			animation.make_new_frame();
			animation[TEXT].clear();
		}

		unsigned k = CH.size();
		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(CH[k - 2].x, CH[k - 2].y,
									CH[k - 1].x, CH[k - 1].y, gr::YELLOW);

		return CH;
	}

	void make_convex_hull(point_set& P,
						  gr::Animation& animation)
	{
		for (auto p : P)
		{
			animation[POINTS].add_point(p.x, p.y);
		}
		animation.make_new_frame(POINTS, HULL);
		Rotation_order order(P);
		std::sort(P.begin(), P.end(), order);

		convex_hull CH = make_hull(P, animation);

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& v : CH)
		{
			plot_CH.add_vertex(v.x, v.y);
		}
		animation[HULL].clear();
		animation[HULL].add_polygon(plot_CH);
		animation.make_new_frame(POINTS, HULL);
	}
}

int main(int argc, char** argv)
{
	using namespace chap1_rotating_convex_hull;

	chs::Convex_hull_option opt = chs::process_command_line(argc, argv);
	point_set P = chs::make_point_set(opt);

	geo::save_point_2_set("log/Chapter-1/rotating_convex_hull", P);
	gr::Animation animation(NB_FIGURES);
	make_convex_hull(P, animation);

	gr::Display_canvas canvas;
	canvas.set_title("Rotating convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}