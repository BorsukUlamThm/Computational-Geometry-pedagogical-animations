#include <list>
#include "Convex_hull_setup.h"
#include "graphics/View/Display_canvas.h"
#include "geometry/Tools/Point_comparisons.h"


namespace chap1_daq_convex_hull
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::Point_2<int> point;
	typedef std::vector<point> point_set;
	typedef std::list<point> half_hull;

	enum Figures
	{
		POINTS,
		HULL,
		HALF_HULLS,
		TURN,
		NB_FIGURES
	};
	gr::Animation animation(NB_FIGURES);


	void plot_turn(const half_hull& H,
				   const half_hull::iterator it,
				   gr::Color color)
	{
		point p2 = *it;
		point p3 = *std::next(it);

		if (it == H.begin())
		{
			animation[TURN].add_segment(p2.x, p2.y, p3.x, p3.y, color, color);
			return;
		}

		point p1 = *std::prev(it);

		animation[TURN].add_segment(p1.x, p1.y, p2.x, p2.y, color, color);
		animation[TURN].add_segment(p2.x, p2.y, p3.x, p3.y, color, color);
	}

	void plot_half_hull(const half_hull& H,
						gr::Color color = gr::PURPLE)
	{
		if (H.size() == 1)
		{
			int x = H.begin()->x;
			int y = H.begin()->y;
			animation[HALF_HULLS].add_point(x, y, color, 5);
		}


		auto it = H.begin();
		it++;

		for (; it != H.end(); ++it)
		{
			int x1 = (std::prev(it))->x;
			int y1 = (std::prev(it))->y;
			int x2 = it->x;
			int y2 = it->y;
			animation[HALF_HULLS].add_segment(x1, y1, x2, y2, color, color);
		}
	}

	/// returns true iff the three points prev(it), it, next(it) make a left turn
	bool left_turn(const half_hull& H, half_hull::iterator it)
	{
		if (it == H.begin())
		{
			return false;
		}

		auto prev = std::prev(it);
		auto next = std::next(it);
		return geo::point_left_line(*prev, *it, *next);
	}

	void make_convex(half_hull& H)
	{
		auto it = std::next(H.begin());

		while (it != std::prev(H.end()))
		{
			while (left_turn(H, it))
			{
				plot_half_hull(H);
				plot_turn(H, it, gr::RED);
				animation.make_new_frame(POINTS, HALF_HULLS, TURN);
				animation[HALF_HULLS].clear();
				animation[TURN].clear();
				it = H.erase(it);
				--it;
			}
			plot_half_hull(H);
			plot_turn(H, it, gr::GREEN);
			animation.make_new_frame(POINTS, HALF_HULLS, TURN);
			animation[HALF_HULLS].clear();
			animation[TURN].clear();
			++it;
		}
	}

	half_hull upper_merge(half_hull& UH1, half_hull& UH2)
	{
		plot_half_hull(UH1);
		plot_half_hull(UH2);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		UH1.merge(UH2, geo::point_left_point<int>);
		plot_half_hull(UH1);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		make_convex(UH1);
		plot_half_hull(UH1, gr::YELLOW);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		return UH1;
	}

	half_hull lower_merge(half_hull& LH1, half_hull& LH2)
	{
		plot_half_hull(LH1);
		plot_half_hull(LH2);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		LH1.merge(LH2, geo::point_right_point<int>);
		plot_half_hull(LH1);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		make_convex(LH1);
		plot_half_hull(LH1, gr::YELLOW);
		animation.make_new_frame(POINTS, HALF_HULLS);
		animation[HALF_HULLS].clear();

		return LH1;
	}

	half_hull daq_upper_hull(const point_set& P, unsigned i, unsigned j)
	{
		half_hull H;
		if (j - i == 0)
		{
			return H;
		}
		if (j - i == 1)
		{
			H.push_back(P[i]);
			return H;
		}

		half_hull UH1 = daq_upper_hull(P, i, (i + j) / 2);
		half_hull UH2 = daq_upper_hull(P, (i + j) / 2, j);

		return upper_merge(UH1, UH2);
	}

	half_hull daq_lower_hull(const point_set& P, unsigned i, unsigned j)
	{
		half_hull H;
		if (j - i == 0)
		{
			return H;
		}
		if (j - i == 1)
		{
			H.push_back(P[i]);
			return H;
		}

		half_hull UH1 = daq_lower_hull(P, i, (i + j) / 2);
		half_hull UH2 = daq_lower_hull(P, (i + j) / 2, j);

		return lower_merge(UH1, UH2);
	}

	void daq_convex_hull(const point_set& P)
	{
		for (auto p : P)
		{
			animation[POINTS].add_point(p.x, p.y);
		}
		animation.make_new_frame(POINTS);

		unsigned n = P.size();
		half_hull U = daq_upper_hull(P, 0, n);
		half_hull L = daq_lower_hull(P, 0, n);

		U.pop_back();
		L.pop_back();
		U.splice(U.end(), L);

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
	using namespace chap1_daq_convex_hull;

	chs::Convex_hull_option opt = chs::process_command_line(argc, argv);
	point_set P = chs::make_point_set(opt);

	geo::save_point_2_set("log/Chapter-1/daq_convex_hull", P);
	daq_convex_hull(P);

	gr::Display_canvas canvas;
	canvas.set_title("Divide and conquer convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}