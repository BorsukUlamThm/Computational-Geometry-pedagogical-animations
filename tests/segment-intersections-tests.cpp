#include "geometry/algorithms/segment_intersections.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/random_generation.h"
#include "graphics/view/Acquisition_canvas.h"
#include "graphics/view/Animation_canvas.h"


namespace geo = geometry;
namespace gr = graphics;

int main()
{
	//	gr::Acquisition_canvas canvas;
	//	canvas.add_segment_acquisition();
	//	gr::Acquisitions acquisitions = canvas.acquire_buffer();
	//	std::vector<gr::Segment_obj> segments =
	//			acquisitions[0]->get_objects<gr::Segment_obj>();
	//
	//	std::vector<geo::segment_2> S;
	//	for (auto& s : segments)
	//	{
	//		S.emplace_back(s.origin.abscissa, s.origin.ordinate,
	//					   s.destination.abscissa, s.destination.ordinate);
	//	}
	//
	//	geo::save_segment_2_set("log/tests/segment_intersections_tests", S);

	//	std::vector<geo::segment_2> S =
	//			geo::load_segment_2_set("saved_inputs/si_goal");

	//	std::vector<geo::segment_2> S =
	//			geo::load_segment_2_set("saved_inputs/si_bug");

	geo::Number_generator ng;
	std::vector<geo::segment_2> S = ng.random_segment_2_set(50);

	geo::DCEL D = segment_intersections(S);

	std::cout << D << std::endl;

	std::cout << D.is_valid(geo::DCEL::VERTICES_CHECK |
							geo::DCEL::HEDGES_CHECK) << std::endl;

	gr::Figure fig;
	for (auto& h : D.half_edges)
	{
		gr::Coordinate x1(h->origin->x);
		gr::Coordinate y1(h->origin->y);
		gr::Coordinate x2(h->twin->origin->x);
		gr::Coordinate y2(h->twin->origin->y);

		fig.add_segment(x1, y1, x2, y2);
	}
	for (auto& v : D.vertices)
	{
		gr::Coordinate x(v->x);
		gr::Coordinate y(v->y);

		fig.add_point(x, y, gr::RED);
	}

	gr::Animation_canvas canvas_1;
	//	canvas_1.display_figure(fig);

	return 0;
}