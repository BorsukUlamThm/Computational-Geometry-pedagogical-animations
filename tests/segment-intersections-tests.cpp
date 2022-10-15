#include "geometry/algorithms/segment_intersections.h"
#include "geometry/algorithms/segment_intersections_components/sic_utils.h"
#include "geometry/algorithms/segment_intersections_components/face_computation.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/random_generation.h"
#include "graphics/view/Acquisition_canvas.h"
#include "graphics/view/Animation_canvas.h"


namespace geo = geometry;
namespace sic = geo::segment_intersections_components;
namespace gr = graphics;

void plot_face_bound(gr::Figure& fig,
					 geo::DCEL::hedge* h)
{
	geo::DCEL::hedge* h1 = h;
	do
	{
		gr::Coordinate x1(h1->origin->x);
		gr::Coordinate y1(h1->origin->y);
		gr::Coordinate x2(h1->twin->origin->x);
		gr::Coordinate y2(h1->twin->origin->y);

		fig.add_half_edge(x1, y1, x2, y2, gr::RED);
		h1 = h1->next;
	}
	while (h1 != h);
}

void plot_face(gr::Figure& fig,
			   geo::DCEL::face* f)
{
	if (f->outer_comp)
	{
		plot_face_bound(fig, f->outer_comp);
	}
	for (auto& h : f->inner_comp)
	{
		plot_face_bound(fig, h);
	}
}

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

	//	std::vector<geo::segment_2> S =
	//			geo::load_segment_2_set("saved_inputs/si_test_2");

	geo::Number_generator ng;
	std::vector<geo::segment_2> S = ng.random_segment_2_set(20);

	geo::save_segment_2_set("log/tests/segment_intersections_tests", S);
	geo::DCEL D = segment_intersections(S);

	std::cout << D << std::endl << std::endl;

	std::cout << "D is " <<
			  (D.is_valid() ? "" : "NOT ")
			  << "valid" << std::endl;

	gr::Animation animation(4);
	for (auto& h : D.half_edges)
	{
		gr::Coordinate x1(h->origin->x);
		gr::Coordinate y1(h->origin->y);
		gr::Coordinate x2(h->twin->origin->x);
		gr::Coordinate y2(h->twin->origin->y);

		animation[0].add_half_edge(x1, y1, x2, y2);
	}

	animation.make_new_frame();

	//	for (auto& v : D.vertices)
	//	{
	//		gr::Coordinate x(v->x);
	//		gr::Coordinate y(v->y);
	//
	//		fig.add_point(x, y, gr::RED);
	//	}

	//	for (auto& l : L)
	//	{
	//		gr::Coordinate xl(l.leftmost->origin->x);
	//		gr::Coordinate yl(l.leftmost->origin->y);
	//
	//		if (l.helper)
	//		{
	//			gr::Coordinate xh(l.helper->origin->x);
	//			gr::Coordinate yh(l.helper->origin->y);
	//
	//			fig.add_segment(xl, yl, xh, yh, gr::RED);
	//		}
	//		else
	//		{
	//			fig.add_point(xl, yl, gr::RED);
	//		}
	//	}

	for (auto& f : D.faces)
	{
		animation[1].clear();
		plot_face(animation[1], f);
		animation.make_new_frame();
	}

	gr::Animation_canvas canvas_1;
	canvas_1.run_animation(animation);

	return 0;
}