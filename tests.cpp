#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <boost/program_options.hpp>

namespace gr = graphics;
namespace alg = algorithms;

typedef alg::Point_2<int> Point;
typedef std::vector<alg::Point_2<int>> Points;
typedef alg::Segment_2<int> Segment;
typedef std::vector<alg::Segment_2<int>> Segments;

Points make_points(const gr::Acquisition& acquisition)
{
	Points points;
	for(unsigned i = 0; i < acquisition.get_size(); ++i)
	{
		auto acquired_point = std::dynamic_pointer_cast
				<gr::Acquired_point>(acquisition[i]);

		gr::Coordinate x = acquired_point->abscissa;
		gr::Coordinate y = acquired_point->ordinate;
		points.emplace_back(int(x), int(y));
	}

	return points;
}

Segments make_segments(const gr::Acquisition& acquisition)
{
	Segments segments;
	for(unsigned i = 0; i < acquisition.get_size(); ++i)
	{
		auto acquired_segment = std::dynamic_pointer_cast
				<gr::Acquired_segment>(acquisition[i]);

		gr::Coordinate ogn_x = acquired_segment->origin_x;
		gr::Coordinate ogn_y = acquired_segment->origin_y;
		gr::Coordinate dst_x = acquired_segment->destination_x;
		gr::Coordinate dst_y = acquired_segment->destination_y;
		segments.emplace_back(int(ogn_x), int(ogn_y), int(dst_x), int(dst_y));
	}

	return segments;
}


int main()
{

	gr::Acquisition_canvas canvas;
	canvas.add_point_acquisition(-1, gr::RED, 15);
	canvas.add_segment_acquisition(4, gr::YELLOW, gr::GREEN);
	canvas.add_point_acquisition(2, gr::BLUE, 10);

	gr::Acquisitions acquisitions = canvas.acquire_buffer();

	Points points0 = make_points(*acquisitions[0]);
	Segments segments = make_segments(*acquisitions[1]);
	Points points1 = make_points(*acquisitions[2]);

	std::cout << std::endl;
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