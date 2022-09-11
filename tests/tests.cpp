#include "graphics/view/Display_canvas.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/DCEL/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/utils/Event_queue.h"
#include "geometry/utils/line_intersections.h"


namespace gr = graphics;
namespace geo = geometry;

typedef geo::Point_2<long int> point;
typedef geo::Segment_2<long int> segment;

void test()
{
	gr::Acquisition_canvas canvas;
	canvas.add_segment_acquisition(2);
	gr::Acquisitions acquisitions = canvas.acquire_buffer();
	auto segments = acquisitions[0]->get_objects<gr::Segment_obj>();

	segment s0(segments[0].origin.abscissa,
			   segments[0].origin.ordinate,
			   segments[0].destination.abscissa,
			   segments[0].destination.ordinate);
	segment s1(segments[1].origin.abscissa,
			   segments[1].origin.ordinate,
			   segments[1].destination.abscissa,
			   segments[1].destination.ordinate);
	point p = geo::line_intersection(s0, s1);

	std::cout << "s0 : " << s0 << std::endl
			  << "s1 : " << s1 << std::endl << std::endl;

	gr::Figure fig;
	fig.add_segment(s0.p1.x, s0.p1.y, s0.p2.x, s0.p2.y);
	fig.add_segment(s1.p1.x, s1.p1.y, s1.p2.x, s1.p2.y);
	fig.add_point(p.x, p.y,
				  geo::segment_intersect(s0, s1) ? gr::YELLOW : gr::RED);
	gr::Display_canvas canvas_;
	canvas_.display_figure(fig);
}

int main(int argc, char** argv)
{
	//	while (true)
	//	{
	//		test();
	//	}

	std::cout << std::numeric_limits<long int>::min() << std::endl;

	segment s0(1536, 238, 1575, 832);
	segment s1(1037, 808, 1820, 977);
	std::cout << geo::segment_intersect(s0, s1);

	gr::Figure fig;
	fig.add_segment(s0.p1.x, s0.p1.y, s0.p2.x, s0.p2.y);
	fig.add_segment(s1.p1.x, s1.p1.y, s1.p2.x, s1.p2.y);
	gr::Display_canvas canvas_;
	canvas_.display_figure(fig);

	return 0;
}