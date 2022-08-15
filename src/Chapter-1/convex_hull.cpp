#include "../../include/Convex_hull_setup.h"
#include "graphics/View/Display_canvas.h"
#include "geometry/Tools/Point_comparisons.h"


namespace chap1_convex_hull
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
		NB_FIGURES
	};
	gr::Animation animation(NB_FIGURES);


	bool left_turn(const convex_hull& hull, const point& p)
	{
		if (hull.size() < 2)
		{
			return false;
		}

		unsigned n = hull.size();
		return geo::point_left_line(p, hull[n - 2], hull[n - 1]);
	}

	convex_hull make_upper_hull(const point_set& P)
	{
		unsigned n = P.size();
		animation[LINE].add_vertical_line(P[0].x);
		animation.make_new_frame();

		convex_hull U;
		U.push_back(P[0]);
		U.push_back(P[1]);

		animation[HULL].add_segment(P[0].x, P[0].y,
									P[1].x, P[1].y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_vertical_line(P[1].x);
		animation.make_new_frame();

		for (unsigned i = 2; i < n; ++i)
		{
			unsigned k = U.size();
			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(U[k - 2].x, U[k - 2].y,
										U[k - 1].x, U[k - 1].y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_vertical_line(P[i].x);

			while (left_turn(U, P[i]))
			{
				animation[HULL].add_segment(U.back().x, U.back().y,
											P[i].x, P[i].y, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				U.pop_back();
			}
			animation[HULL].add_segment(U.back().x, U.back().y,
										P[i].x, P[i].y, gr::GREEN);
			U.push_back(P[i]);
			animation.make_new_frame();
		}

		unsigned k = U.size();
		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(U[k - 2].x, U[k - 2].y,
									U[k - 1].x, U[k - 1].y, gr::YELLOW);

		return U;
	}

	convex_hull make_lower_hull(const point_set& P)
	{
		unsigned n = P.size();
		animation.make_new_frame();

		convex_hull L;
		L.push_back(P[n - 1]);
		L.push_back(P[n - 2]);

		animation[HULL].add_segment(P[n - 1].x, P[n - 1].y,
									P[n - 2].x, P[n - 2].y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_vertical_line(P[n - 2].x);
		animation.make_new_frame();

		for (unsigned i = n - 3; i < n; --i)
		{
			unsigned k = L.size();
			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(L[k - 2].x, L[k - 2].y,
										L[k - 1].x, L[k - 1].y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_vertical_line(P[i].x);

			while (left_turn(L, P[i]))
			{
				animation[HULL].add_segment(L.back().x, L.back().y,
											P[i].x, P[i].y, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				L.pop_back();
			}
			animation[HULL].add_segment(L.back().x, L.back().y,
										P[i].x, P[i].y, gr::GREEN);
			L.push_back(P[i]);
			animation.make_new_frame();
		}

		unsigned k = L.size();
		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(L[k - 2].x, L[k - 2].y,
									L[k - 1].x, L[k - 1].y, gr::YELLOW);
		animation.make_new_frame();

		return L;
	}

	void make_convex_hull(point_set& P)
	{
		for (auto p : P)
		{
			animation[POINTS].add_point(p.x, p.y);
		}
		animation.make_new_frame();

		std::sort(P.begin(), P.end(), geo::point_left_point<int>);

		convex_hull U = make_upper_hull(P);
		convex_hull L = make_lower_hull(P);

		U.pop_back();
		L.pop_back();

		for (auto& p : L)
		{
			U.push_back(p);
		}

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& v : U)
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
	using namespace chap1_convex_hull;

	chs::Convex_hull_option opt = chs::process_command_line(argc, argv);
	point_set P = chs::make_point_set(opt);

	geo::save_point_2_set("log/Chapter-1/convex_hull", P);
	make_convex_hull(P);

	gr::Display_canvas canvas;
	canvas.set_title("Convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}