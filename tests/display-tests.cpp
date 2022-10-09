#include "graphics/view/Animation_canvas.h"


namespace gr = graphics;

int main()
{
	gr::Point_shp point_shp(0, 0, gr::BLUE, 20);
	gr::Segment_shp segment_shp(1, 0, 2, 1, gr::RED, gr::GREEN);
	gr::Vector_shp vector_shp(3, 0, 4, 1, gr::YELLOW);
	gr::Half_edge_shp half_edge1_shp(5, 0, 6, 1, gr::RED, gr::YELLOW);
	gr::Half_edge_shp half_edge2_shp(6, 1, 5, 0, gr::BLUE, gr::YELLOW);
	gr::Circle_shp circle_shp(7.5, 0.5, 0.5, gr::GREEN);
	gr::Polygon_shp polygon_shp(gr::PURPLE, gr::RED);
	polygon_shp.add_vertex(9, 0);
	polygon_shp.add_vertex(10, 0);
	polygon_shp.add_vertex(10, 1);
	polygon_shp.add_vertex(9.5, 1.5);
	polygon_shp.add_vertex(9, 1);
	gr::Line_shp line_shp(0, 1, -2, gr::BLUE);
	gr::Text_shp text_shp("some random text", 1, -1, 30);

	gr::Figure fig;
	fig.add_point(point_shp);
	fig.add_segment(segment_shp);
	fig.add_vector(vector_shp);
	fig.add_half_edge(half_edge1_shp);
	fig.add_half_edge(half_edge2_shp);
	fig.add_circle(circle_shp);
	fig.add_polygon(polygon_shp);
	fig.add_line(line_shp);
	fig.add_text(text_shp);

	gr::Animation_canvas canvas;
	canvas.display_figure(fig);

	fig.save("test");

	gr::Figure fig2;
	fig2.load("test");
	canvas.display_figure(fig2);

	return 0;
}