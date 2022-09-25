#include "geometry/algorithms/convex_hull.h"
#include "graphics/view/Animation_canvas.h"
#include "geometry/utils/random_generation.h"


namespace geo = geometry;
namespace gr = graphics;
typedef geo::point_2 point;
typedef std::vector<point> point_set;

int main(int argc, char** argv)
{
	geo::Number_generator ng;
	std::vector<point> P = ng.random_point_2_set(50);

	geo::DCEL dcel = geo::convex_hull(P);

	std::cout << "dcel is "
			  << (dcel.is_valid() ? "" : "NOT ")
			  << "valid"
			  << std::endl;

	gr::Figure fig;
	for (auto& h : dcel.half_edges)
	{
		gr::Coordinate x1(h->origin->x);
		gr::Coordinate y1(h->origin->y);
		gr::Coordinate x2(h->twin->origin->x);
		gr::Coordinate y2(h->twin->origin->y);

		fig.add_segment(x1, y1, x2, y2, gr::YELLOW);
	}
	for (auto& p : P)
	{
		gr::Coordinate x(p.x);
		gr::Coordinate y(p.y);

		fig.add_point(x, y);
	}

	gr::Animation_canvas canvas;
	canvas.display_figure(fig);

	return 0;
}