#include <iostream>
#include "graphics/View/Display_canvas.h"
#include "graphics/View/Acquisition_canvas.h"

namespace gr = graphics;
void display_tests()
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

	std::string str = "é";
	sf::String s (str);

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
}
void acquisition_tests()
{
	gr::Acquisition_canvas canvas;
	canvas.add_point_acquisition(3, gr::BLUE, 20);
	canvas.add_segment_acquisition(-1, gr::RED, gr::YELLOW);

	auto acq = canvas.acquire_buffer();

	std::cout << std::endl;
}

int main()
{
	display_tests();

	return 0;
}


/*
namespace po = boost::program_options;
using namespace std;

int main(int argc, const char** argv)
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("compression", po::value<int>(), "set compression level")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        cout << "Compression level was not set.\n";
    }
}
 */