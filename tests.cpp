#include "Graphics/View/View.h"
//#include "Algorithms/Algorithms.h"
//#include <boost/program_options.hpp>
#include <map>
#include <iostream>


namespace gr = graphics;
//namespace alg = algorithms;

int main()
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

	std::string str = text_shp.get_content();
	std::cout << str << std::endl;

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