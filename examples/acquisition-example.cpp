#include "graphics/view/Acquisition_canvas.h"


namespace gr = graphics;

int main()
{
	gr::Acquisition_canvas canvas;

	// declare the acquisitions

	// an arbitrary number of points
	canvas.add_point_acquisition();

	// 2 blue segments with yellow endpoints
	canvas.add_segment_acquisition(2, gr::BLUE, gr::YELLOW);

	// 3 red points with radius 10
	canvas.add_point_acquisition(3, gr::RED, 10);

	// 2 green polygon with blue vertices
	canvas.add_polygon_acquisition(2, gr::GREEN, gr::BLUE);

	// all those declaration are stored in the canvas buffer
	// open the canvas and begin the acquisition
	gr::Acquisitions acquisitions = canvas.acquire_buffer();

	// acquisitions contains now all the acquired objects
	// acquisitions[i] contains the i-th acquisition
	// the Geometric_object can be extracted this way
	std::vector<gr::Point_obj> points =
			acquisitions[0]->get_objects<gr::Point_obj>();
	std::vector<gr::Segment_obj> segments =
			acquisitions[1]->get_objects<gr::Segment_obj>();
	std::vector<gr::Point_obj> red_points =
			acquisitions[2]->get_objects<gr::Point_obj>();
	std::vector<gr::Polygon_obj> polygons =
			acquisitions[3]->get_objects<gr::Polygon_obj>();

	std::cout << "first points acquired ("
			  << points.size()
			  << "):"
			  << std::endl;
	for (auto& p : points)
	{
		std::cout << p << std::endl;
	}
	std::cout << std::endl;

	std::cout << "segments:" << std::endl;
	for (auto& s : segments)
	{
		std::cout << s << std::endl;
	}
	std::cout << std::endl;

	std::cout << "red points:" << std::endl;
	for (auto& p : red_points)
	{
		std::cout << p << std::endl;
	}
	std::cout << std::endl;

	std::cout << "polygons:\n[ ";
	for (auto& p : polygons[0])
	{
		std::cout << "(" << p << ") ";
	}
	std::cout << "]\n[ ";
	for (auto& p : polygons[1])
	{
		std::cout << "(" << p << ") ";
	}
	std::cout << "]" << std::endl;

	return 0;
}