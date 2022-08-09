#include <boost/program_options.hpp>
#include <iostream>

int main()
{
	std::string s {"`a"};
	std::vector<std::string> vec;
	vec.emplace_back("b");
	vec.emplace_back("c");
	vec.emplace_back("d`");

	s = s.substr(1, s.size() - 1);
	unsigned i = 0;
	while(i < vec.size() && vec[i][vec[i].size() - 1] != '`')
	{
		s += vec[i];
		++i;
	}
	s += vec[i].substr(0, vec[i].size() - 1);

	std::cout << s << std::endl << std::endl;

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