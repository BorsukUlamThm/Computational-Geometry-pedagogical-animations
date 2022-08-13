#include "Convex_hull_setup.h"


namespace chap1_rotating_convex_hull
{
	namespace gr = graphics;
	namespace alg = algorithms;

	typedef alg::Point_2<int> point;
	typedef std::vector<point> convex_hull;
	typedef std::vector<point> point_set;

	gr::Slide_show slides;
	gr::Figure fig_points;
	gr::Figure fig_hull;
	gr::Figure fig_line;


	struct Rotation_order
	{
		point leftmost_point;

		Rotation_order(const point_set& P)
		{
			leftmost_point = P[0];
			for(auto& p : P)
			{
				if(alg::point_left_point(p, leftmost_point))
				{
					leftmost_point = p;
				}
			}
		}

		bool operator()(const point& p, const point& q) const
		{
			if(p == q)
			{
				return true;
			}
			if(p == leftmost_point)
			{
				return true;
			}
			if(q == leftmost_point)
			{
				return false;
			}

			return alg::point_left_line(q, leftmost_point, p);
		}
	};

	bool right_turn(const convex_hull& hull, const point& p)
	{
		if(hull.size() < 2)
		{
			return false;
		}

		unsigned n = hull.size();
		return alg::point_right_line(p, hull[n - 2], hull[n - 1]);
	}

	convex_hull make_hull(const point_set& P)
	{
		unsigned n = P.size();
		fig_line.add_vertical_line(P[0].x);
		slides.add_slide(fig_points, fig_line);

		convex_hull CH;
		CH.push_back(P[0]);
		CH.push_back(P[1]);

		fig_hull.add_segment(P[0].x, P[0].y,
							 P[1].x, P[1].y, gr::YELLOW);
		fig_line.clear();
		fig_line.add_line(P[0].x, P[0].y, P[1].x, P[1].y);
		slides.add_slide(fig_points, fig_line, fig_hull);

		for(unsigned i = 2; i < n; ++i)
		{
			unsigned k = CH.size();
			fig_hull.erase_last_shape();
			fig_hull.add_segment(CH[k - 2].x, CH[k - 2].y,
								 CH[k - 1].x, CH[k - 1].y, gr::YELLOW);
			fig_line.clear();
			fig_line.add_line(P[0].x, P[0].y, P[i].x, P[i].y);

			while(right_turn(CH, P[i]))
			{
				fig_hull.add_segment(CH.back().x, CH.back().y,
									 P[i].x, P[i].y, gr::RED);
				slides.add_slide(fig_points, fig_line, fig_hull);
				fig_hull.erase_last_k_shapes(2);
				CH.pop_back();
			}
			fig_hull.add_segment(CH.back().x, CH.back().y,
								 P[i].x, P[i].y, gr::GREEN);
			CH.push_back(P[i]);
			slides.add_slide(fig_points, fig_line, fig_hull);
		}

		unsigned k = CH.size();
		fig_hull.erase_last_shape();
		fig_hull.add_segment(CH[k - 2].x, CH[k - 2].y,
							 CH[k - 1].x, CH[k - 1].y, gr::YELLOW);

		return CH;
	}

	void make_convex_hull(point_set& P)
	{
		for(auto p : P)
		{
			fig_points.add_point(p.x, p.y);
		}
		slides.add_slide(fig_points);

		Rotation_order order(P);
		std::sort(P.begin(), P.end(), order);

		convex_hull CH = make_hull(P);

		gr::Polygon_shp plot_CH(gr::YELLOW);
		for(auto& v : CH)
		{
			plot_CH.add_vertex(v.x, v.y);
		}
		fig_hull.clear();
		fig_hull.add_polygon(plot_CH);
		slides.add_slide(fig_points, fig_hull);
	}
}

int main(int argc, char** argv)
{
	using namespace chap1_rotating_convex_hull;

	chs::Convex_hull_option opt = chs::process_command_line(argc, argv);
	point_set P = chs::make_point_set(opt);

	alg::save_point_2_set("log/Chapter-1/rotating_convex_hull", P);
	make_convex_hull(P);

	gr::Display_canvas canvas;
	canvas.set_title("Rotating convex hull - animation");
	canvas.display_slide_show(slides);

	return 0;
}