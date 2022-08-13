#include "Graphics/View/View.h"
#include "Algorithms/Algorithms.h"
#include <boost/program_options.hpp>


namespace gr = graphics;
namespace alg = algorithms;

int main()
{
	unsigned n = -1;

	for (unsigned a = 0; a < 11; ++a)
	{
		unsigned b = 1 << a;
		std::cout << b << std::endl;
	}

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