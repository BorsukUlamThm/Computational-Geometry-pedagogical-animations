#include <iostream>
#include <boost/program_options.hpp>
#include "graphics/View/Display_canvas.h"
#include "graphics/View/Acquisition_canvas.h"
#include "utils/Program_options.h"

namespace gr = graphics;
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
	gr::Text_shp text_shp("Les étoiles sont plus belles les yeux fermés",
						  0, -1, 30);

	//	std::cout << circle_shp << std::endl;
	//	gr::Circle_shp circle_shp2;
	//	std::cin >> circle_shp2;
	//	std::cout << circle_shp2 << std::endl;
	//
	//	return 0;

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
int acquisition_tests()
{
	gr::Acquisition_canvas canvas;
	canvas.add_point_acquisition(3, gr::BLUE, 20);
	canvas.add_segment_acquisition(-1, gr::RED, gr::YELLOW);

	auto acq = canvas.acquire_buffer();

	auto dummy = acq[0]->get_objects<gr::Point_obj>();
	for(auto& pt : dummy)
	{
		std::cout << pt << std::endl;
	}

	return 0;
}

int program_option_tests(int argc, char** argv)
{
	utils::Program_options options;
	options.add_option("aaaa", "a");
	options.add_option("bbbb", "b");
	options.add_option("cccc", "c");

	options.parse_command_line(argc, argv);

	return 0;
}

int main(int argc, char** argv)
{
	return acquisition_tests();
}