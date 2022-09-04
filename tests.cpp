#include "graphics/view/Display_canvas.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/DCEL/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/polygon_utils.h"


namespace gr = graphics;
namespace geo = geometry;

int display_tests()
{
	gr::Point_shp point_shp(0, 0, gr::BLUE, 20);
	gr::Segment_shp segment_shp(1, 0, 2, 1, gr::RED, gr::GREEN);
	gr::Vector_shp vector_shp(3, 0, 4, 1, gr::YELLOW);
	gr::Circle_shp circle_shp(5.5, 0.5, 0.5, gr::GREEN);
	gr::Polygon_shp polygon_shp(gr::PURPLE, gr::RED);
	polygon_shp.add_vertex(7, 0);
	polygon_shp.add_vertex(8, 0);
	polygon_shp.add_vertex(8, 1);
	polygon_shp.add_vertex(7.5, 1.5);
	polygon_shp.add_vertex(7, 1);
	gr::Line_shp line_shp(0, 1, -2, gr::BLUE);
	gr::Text_shp text_shp("some random text",
						  0, -1, 30);

	gr::Figure fig;
	fig.add_point(point_shp);
	fig.add_segment(segment_shp);
	fig.add_vector(vector_shp);
	fig.add_circle(circle_shp);
	fig.add_polygon(polygon_shp);
	fig.add_line(line_shp);
	fig.add_text(text_shp);

	gr::Display_canvas canvas;
	canvas.display_figure(fig);

	fig.save("test");

	gr::Figure fig2;
	fig2.load("test");
	canvas.display_figure(fig2);

	return 0;
}

int main(int argc, char** argv)
{
	typedef geo::DCEL::rational rational;

	geo::Polygon<rational> P;
	P.emplace_back(0, 0);
	P.emplace_back(1, 0);
	P.emplace_back(0, 1);

	geo::DCEL::DCEL dcel(P);
	std::cout << dcel << std::endl;

	return 0;
}