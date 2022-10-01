#include "geometry/model/DCEL.h"
#include "geometry/utils/polygon_utils.h"


namespace geo = geometry;

int main()
{
	geo::polygon P;
	P.emplace_back(0, 0);
	P.emplace_back(1, 0);
	P.emplace_back(1, 1);
	P.emplace_back(0, 1);

	geo::DCEL D = geo::DCEL_from_polygon(P);

	std::cout << "D is "
			  << (D.is_valid() ? "" : "NOT ")
			  << "valid"
			  << std::endl;

	P.clear();
	P.emplace_back(0, 1);
	P.emplace_back(1, 1);
	P.emplace_back(1, 0);
	P.emplace_back(0, 0);

	geo::DCEL dcel1 = geo::DCEL_from_polygon(P);

	std::cout << "D is "
			  << (dcel1.is_valid() ? "" : "NOT ")
			  << "valid"
			  << std::endl;

	return 0;
}