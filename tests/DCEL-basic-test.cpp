#include "geometry/DCEL/DCEL.h"
#include "geometry/utils/polygon_utils.h"


namespace geo = geometry;

int main(int argc, char** argv)
{
	geo::polygon P;
	P.emplace_back(0, 0);
	P.emplace_back(1, 0);
	P.emplace_back(1, 1);
	P.emplace_back(0, 1);

	geo::DCEL dcel(P);

	std::cout << "dcel is "
			  << (dcel.is_valid() ? "" : "NOT ")
			  << "valid" << std::endl;

	P.clear();
	P.emplace_back(0, 1);
	P.emplace_back(1, 1);
	P.emplace_back(1, 0);
	P.emplace_back(0, 0);

	geo::DCEL dcel1(P);

	std::cout << "dcel is "
			  << (dcel1.is_valid() ? "" : "NOT ")
			  << "valid";

	return 0;
}