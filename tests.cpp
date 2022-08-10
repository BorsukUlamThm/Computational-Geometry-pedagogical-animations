#include "Graphics/View/View.h"

int main()
{
	gr::Point_plot point_plot(1, 1);
	gr::Segment_plot segment_plot(1, 2, 4, 5);
	gr::Vector_plot vector_plot(1, 2, 4, 5);
	gr::Polygon_plot polygon_plot;

	gr::Bounding_box bounding_box;

	bounding_box.extend(point_plot);
	bounding_box.extend(vector_plot);

	std::cout << bounding_box.get_min_abscissa() << " "
			  << bounding_box.get_max_abscissa() << " "
			  << bounding_box.get_min_ordinate() << " "
			  << bounding_box.get_max_ordinate() << std::endl;


	return 0;
}






//namespace po = boost::program_options;
//using namespace std;
//
//int main(int argc, const char** argv)
//{
//    // Declare the supported options.
//    po::options_description desc("Allowed options");
//    desc.add_options()
//            ("help", "produce help message")
//            ("compression", po::value<int>(), "set compression level")
//            ;
//
//    po::variables_map vm;
//    po::store(po::parse_command_line(argc, argv, desc), vm);
//    po::notify(vm);
//
//    if (vm.count("help")) {
//        cout << desc << "\n";
//        return 1;
//    }
//
//    if (vm.count("compression")) {
//        cout << "Compression level was set to "
//             << vm["compression"].as<int>() << ".\n";
//    } else {
//        cout << "Compression level was not set.\n";
//    }
//}