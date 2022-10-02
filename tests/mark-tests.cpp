#include "geometry/model/DCEL.h"
#include "geometry/utils/polygon_utils.h"
#include <iostream>


namespace geo = geometry;

void print_marks(const geo::DCEL& D,
				 geo::DCEL::mark_t m)
{
	std::cout << "vertices marks :";
	for (unsigned i = 0; i < D.vertices.size(); ++i)
	{
		if (D.vertices[i]->is_marked(m))
		{ std::cout << " " << i; }
	}
	//	std::cout << std::endl << "half edges marks :";
	//	for (unsigned i = 0; i < D.half_edges.size(); ++i)
	//	{
	//		if (D.half_edges[i]->is_marked(m))
	//		{ std::cout << " " << i; }
	//	}
	//	std::cout << std::endl << "faces marks :";
	//	for (unsigned i = 0; i < D.faces.size(); ++i)
	//	{
	//		if (D.faces[i]->is_marked(m))
	//		{ std::cout << " " << i; }
	//	}
	//	std::cout << std::endl;
}

int main()
{
	geo::point_2 a(0, 0);
	geo::point_2 b(1, 0);
	geo::point_2 c(1, 1);
	geo::point_2 d(0, 1);
	geo::polygon P = {a, b, c, d};
	geo::DCEL D = geo::DCEL_from_polygon(P);

	geo::DCEL::mark_t m1 = D.get_new_mark();
	geo::DCEL::mark_t m2 = D.get_new_mark();
	geo::DCEL::mark_t m3 = D.get_new_mark();

	D.vertices[0]->mark(m1);
	D.vertices[1]->mark(m1);
	D.vertices[2]->mark(m2);
	D.vertices[3]->mark(m3);

	std::cout << "m1 marks" << std::endl;
	print_marks(D, m1);
	std::cout << std::endl << "m2 marks" << std::endl;
	print_marks(D, m2);
	std::cout << std::endl << "m3 marks" << std::endl;
	print_marks(D, m3);

	D.vertices[0]->unmark(m1);
	D.vertices[1]->unmark(m2);

	std::cout << std::endl << std::endl << "m1 marks" << std::endl;
	print_marks(D, m1);
	std::cout << std::endl << "m2 marks" << std::endl;
	print_marks(D, m2);
	std::cout << std::endl << "m3 marks" << std::endl;
	print_marks(D, m3);

	D.free_mark(m2);

	std::cout << std::endl << std::endl << "m1 marks" << std::endl;
	print_marks(D, m1);
	std::cout << std::endl << "m2 marks" << std::endl;
	print_marks(D, m2);
	std::cout << std::endl << "m3 marks" << std::endl;
	print_marks(D, m3);

	m2 = D.get_new_mark();
}