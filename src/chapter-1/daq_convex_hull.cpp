#include <list>
#include "convex_hull_setup.h"
#include "graphics/view/Display_canvas.h"
#include "geometry/utils/point_comparisons.h"


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
		MERGE,
		LINE,
		TEXT,
		NB_FIGURES
	};

	void plot_half_hull(const half_hull& H,
						gr::Color color,
						Figures fig,
						gr::Animation& animation)
	{
		if (H.size() == 1)
		{
			int x = H.begin()->x;
			int y = H.begin()->y;
			animation[fig].add_point(x, y, color, 5);
		}


		auto it = H.begin();
		it++;

		for (; it != H.end(); ++it)
		{
			int x1 = (std::prev(it))->x;
			int y1 = (std::prev(it))->y;
			int x2 = it->x;
			int y2 = it->y;
			animation[fig].add_segment(x1, y1, x2, y2, color, color);
		}
	}

	bool left_turn(const half_hull& H,
				   half_hull::iterator it)
	{
		if (it == H.begin())
		{
			return false;
		}

		auto prev = std::prev(it);
		auto next = std::next(it);
		return geo::point_left_line(*prev, *it, *next);
	}

	void make_convex(half_hull& H,
					 gr::Animation& animation)
	{
		if (H.empty())
		{ return; }

		auto it = std::next(H.begin());
		if (it == H.end())
		{ return; }

		plot_half_hull(H, gr::PURPLE, MERGE, animation);
		animation[LINE].add_vertical_line(H.begin()->x);
		animation.make_new_frame();

		animation[MERGE].add_segment(H.begin()->x, H.begin()->y,
									 it->x, it->y, gr::YELLOW);
		animation[LINE].clear();
		animation[LINE].add_vertical_line(it->x);
		animation.make_new_frame();

		while (it != std::prev(H.end()))
		{
			animation[LINE].clear();
			animation[LINE].add_vertical_line(std::next(it)->x);

			while (left_turn(H, it))
			{
				animation[MERGE].add_segment(std::next(it)->x, std::next(it)->y,
											 it->x, it->y, gr::RED);
				gr::Point_shp point_shp(it->x, it->y);
				animation[TEXT].add_text("deleted", point_shp, 16, gr::RED);
				animation.make_new_frame();
				animation[MERGE].erase_last_k_shapes(2);

				it = H.erase(it);
				--it;
			}
			animation[MERGE].add_segment(std::next(it)->x, std::next(it)->y,
										 it->x, it->y, gr::GREEN);
			gr::Point_shp point_shp(it->x, it->y);
			animation[TEXT].add_text("ok", point_shp, 16, gr::GREEN);
			animation.make_new_frame();
			animation[TEXT].clear();

			++it;
		}

		animation[MERGE].clear();
		animation[LINE].clear();
	}

	half_hull upper_merge(half_hull& UH1,
						  half_hull& UH2,
						  gr::Animation& animation)
	{
		UH1.merge(UH2, geo::point_left_point<int>);
		make_convex(UH1, animation);

		return UH1;
	}

	half_hull lower_merge(half_hull& LH1,
						  half_hull& LH2,
						  gr::Animation& animation)
	{
		LH1.merge(LH2, geo::point_right_point<int>);
		make_convex(LH1, animation);

		return LH1;
	}

	half_hull daq_upper_hull(const point_set& P,
							 unsigned i,
							 unsigned j,
							 gr::Animation& animation)
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

		half_hull UH1 = daq_upper_hull(P, i, (i + j) / 2, animation);
		plot_half_hull(UH1, gr::PURPLE, HALF_HULLS, animation);
		animation.make_new_frame(POINTS, HALF_HULLS);

		half_hull UH2 = daq_upper_hull(P, (i + j) / 2, j, animation);
		plot_half_hull(UH2, gr::PURPLE, HALF_HULLS, animation);
		animation.make_new_frame(POINTS, HALF_HULLS);

		unsigned n1 = (UH1.size() < 2 ? UH1.size() : UH1.size() - 1);
		unsigned n2 = (UH2.size() < 2 ? UH2.size() : UH2.size() - 1);
		animation[HALF_HULLS].erase_last_k_shapes(n1 + n2);

		return upper_merge(UH1, UH2, animation);
	}

	half_hull daq_lower_hull(const point_set& P,
							 unsigned i,
							 unsigned j,
							 gr::Animation& animation)
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

		half_hull LH1 = daq_lower_hull(P, i, (i + j) / 2, animation);
		plot_half_hull(LH1, gr::PURPLE, HALF_HULLS, animation);
		animation.make_new_frame(POINTS, HALF_HULLS);

		half_hull LH2 = daq_lower_hull(P, (i + j) / 2, j, animation);
		plot_half_hull(LH2, gr::PURPLE, HALF_HULLS, animation);
		animation.make_new_frame(POINTS, HALF_HULLS);

		unsigned n1 = (LH1.size() < 2 ? LH1.size() : LH1.size() - 1);
		unsigned n2 = (LH2.size() < 2 ? LH2.size() : LH2.size() - 1);
		animation[HALF_HULLS].erase_last_k_shapes(n1 + n2);

		return lower_merge(LH1, LH2, animation);
	}

	void daq_convex_hull(const point_set& P,
						 gr::Animation& animation)
	{
		for (auto p : P)
		{
			animation[POINTS].add_point(p.x, p.y);
		}
		animation.make_new_frame(POINTS);

		unsigned n = P.size();
		half_hull UH = daq_upper_hull(P, 0, n, animation);
		plot_half_hull(UH, gr::YELLOW, HALF_HULLS, animation);
		half_hull LH = daq_lower_hull(P, 0, n, animation);

		UH.pop_back();
		LH.pop_back();
		UH.splice(UH.end(), LH);

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for (auto& v : UH)
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
	gr::Animation animation(NB_FIGURES);
	daq_convex_hull(P, animation);

	gr::Display_canvas canvas;
	canvas.set_title("Divide and conquer convex hull - animation");
	canvas.run_animation(animation);

	return 0;
}