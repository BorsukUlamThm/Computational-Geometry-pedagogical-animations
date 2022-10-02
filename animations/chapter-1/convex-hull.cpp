#include "include/utils.h"
#include "graphics/view/Animation_canvas.h"
#include "geometry/utils/point_comparisons.h"


namespace chap1_convex_hull
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


	bool left_turn(const convex_hull& hull,
				   const point& p)
	{
		if (hull.size() < 2)
		{
			return false;
		}

		unsigned n = hull.size();
		return geo::point_left_line(p, hull[n - 2], hull[n - 1]);
	}

	convex_hull make_upper_hull(const point_set& P,
								gr::Animation& animation)
	{
		unsigned n = P.size();

		gr::Coordinate P0_x(P[0].x);
		gr::Coordinate P0_y(P[0].y);
		gr::Coordinate P1_x(P[1].x);
		gr::Coordinate P1_y(P[1].y);

		animation[LINE].add_vertical_line(P0_x);
		animation.make_new_frame();

		convex_hull U;
		U.push_back(P[0]);
		U.push_back(P[1]);

		animation[HULL].add_segment(P0_x, P0_y, P1_x, P1_y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_vertical_line(P1_x);
		animation.make_new_frame();

		for (unsigned i = 2; i < n; ++i)
		{
			unsigned k = U.size();
			gr::Coordinate Uk1_x(U[k - 1].x);
			gr::Coordinate Uk1_y(U[k - 1].y);
			gr::Coordinate Uk2_x(U[k - 2].x);
			gr::Coordinate Uk2_y(U[k - 2].y);
			gr::Coordinate Pi_x(P[i].x);
			gr::Coordinate Pi_y(P[i].y);

			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(Uk2_x, Uk2_y, Uk1_x, Uk1_y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_vertical_line(Pi_x);

			while (left_turn(U, P[i]))
			{
				gr::Coordinate Uback_x(U.back().x);
				gr::Coordinate Uback_y(U.back().y);

				animation[HULL].add_segment(Uback_x, Uback_y,
											Pi_x, Pi_y, gr::RED);
				gr::Point_shp point_shp(Uback_x, Uback_y);
				animation[TEXT].add_text("deleted", point_shp, 16, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				U.pop_back();
			}
			gr::Coordinate Uback_x(U.back().x);
			gr::Coordinate Uback_y(U.back().y);

			animation[HULL].add_segment(Uback_x, Uback_y,
										Pi_x, Pi_y, gr::GREEN);
			gr::Point_shp point_shp(Uback_x, Uback_y);
			animation[TEXT].add_text("ok", point_shp, 16, gr::GREEN);
			animation.make_new_frame();
			animation[TEXT].clear();
			U.push_back(P[i]);
		}

		unsigned k = U.size();
		gr::Coordinate Uk1_x(U[k - 1].x);
		gr::Coordinate Uk1_y(U[k - 1].y);
		gr::Coordinate Uk2_x(U[k - 2].x);
		gr::Coordinate Uk2_y(U[k - 2].y);

		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(Uk2_x, Uk2_y, Uk1_x, Uk1_y, gr::YELLOW);

		return U;
	}

	convex_hull make_lower_hull(const point_set& P,
								gr::Animation& animation)
	{
		unsigned n = P.size();

		gr::Coordinate Pn1_x(P[n - 1].x);
		gr::Coordinate Pn1_y(P[n - 1].y);
		gr::Coordinate Pn2_x(P[n - 2].x);
		gr::Coordinate Pn2_y(P[n - 2].y);

		animation.make_new_frame();

		convex_hull L;
		L.push_back(P[n - 1]);
		L.push_back(P[n - 2]);

		animation[HULL].add_segment(Pn1_x, Pn1_y, Pn2_x, Pn2_y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_vertical_line(Pn2_x);
		animation.make_new_frame();

		for (unsigned i = n - 3; i < n; --i)
		{
			unsigned k = L.size();
			gr::Coordinate Lk1_x(L[k - 1].x);
			gr::Coordinate Lk1_y(L[k - 1].y);
			gr::Coordinate Lk2_x(L[k - 2].x);
			gr::Coordinate Lk2_y(L[k - 2].y);
			gr::Coordinate Pi_x(P[i].x);
			gr::Coordinate Pi_y(P[i].y);

			animation[HULL].erase_last_shape();
			animation[HULL].add_segment(Lk2_x, Lk2_y, Lk1_x, Lk1_y, gr::YELLOW);
			animation[LINE].clear();
			animation[LINE].add_vertical_line(Pi_x);

			while (left_turn(L, P[i]))
			{
				gr::Coordinate Lback_x(L.back().x);
				gr::Coordinate Lback_y(L.back().y);

				animation[HULL].add_segment(Lback_x, Lback_y,
											Pi_x, Pi_y, gr::RED);
				gr::Point_shp point_shp(Lback_x, Lback_y);
				animation[TEXT].add_text("deleted", point_shp, 16, gr::RED);
				animation.make_new_frame();
				animation[HULL].erase_last_k_shapes(2);
				L.pop_back();
			}
			gr::Coordinate Lback_x(L.back().x);
			gr::Coordinate Lback_y(L.back().y);

			gr::Point_shp point_shp(Lback_x, Lback_y);
			animation[TEXT].add_text("ok", point_shp, 16, gr::GREEN);
			animation[HULL].add_segment(Lback_x, Lback_y,
										Pi_x, Pi_y, gr::GREEN);
			L.push_back(P[i]);
			animation.make_new_frame();
			animation[TEXT].clear();
		}

		unsigned k = L.size();
		gr::Coordinate Lk1_x(L[k - 1].x);
		gr::Coordinate Lk1_y(L[k - 1].y);
		gr::Coordinate Lk2_x(L[k - 2].x);
		gr::Coordinate Lk2_y(L[k - 2].y);

		animation[HULL].erase_last_shape();
		animation[HULL].add_segment(Lk2_x, Lk2_y, Lk1_x, Lk1_y, gr::YELLOW);
		animation.make_new_frame();

		return L;
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
		animation.make_new_frame();

		std::sort(P.begin(), P.end(), geo::point_left_point);

		convex_hull U = make_upper_hull(P, animation);
		convex_hull L = make_lower_hull(P, animation);

		U.pop_back();
		L.pop_back();

		for (auto& p : L)
		{
			U.push_back(p);
		}

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& p : U)
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
	using namespace chap1_convex_hull;

	Options opt = process_command_line(argc, argv);
	point_set P = make_point_set(opt);

	geo::save_point_2_set("log/chapter-1/convex_hull", P);
	gr::Animation animation(NB_FIGURES);
	make_convex_hull(P, animation);

	gr::Animation_canvas canvas;
	canvas.set_title("Convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}