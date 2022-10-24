#include "geometry/model/DCEL.h"
#include "geometry/model/serialization.h"
#include "graphics/view/Animation_canvas.h"


namespace geo = geometry;
typedef geo::DCEL DCEL;
typedef DCEL::vertex vertex;
typedef DCEL::hedge hedge;
typedef DCEL::face face;

void test(DCEL& D,
		  vertex* v1,
		  vertex* v2)
{
	D.add_diagonal(v1, v2);
	D.faces[0]->inner_comp.pop_back();
	D.half_edges[D.half_edges.size() - 1]->inc_face = D.faces[0];
	D.half_edges[D.half_edges.size() - 2]->inc_face = D.faces[0];
	std::cout << "DCEL is" << (D.is_valid() ? "" : " NOT")
			  << " valid" << std::endl;

	gr::Figure fig;
	D.add_to_figure(fig);

	unsigned nb_hedges = D.half_edges.size();
	hedge* h1 = D.half_edges[nb_hedges - 1];
	hedge* h2 = D.half_edges[nb_hedges - 2];
	h1->add_to_figure(fig, gr::RED);
	h1->prev->add_to_figure(fig, gr::RED);
	h1->next->add_to_figure(fig, gr::RED);
	h2->add_to_figure(fig, gr::BLUE);
	h2->prev->add_to_figure(fig, gr::BLUE);
	h2->next->add_to_figure(fig, gr::BLUE);

	gr::Animation_canvas canvas;
	canvas.display_figure(fig);
}

void test(const std::string& file)
{
	DCEL D1 = geo::load_DCEL(file);
	//	gr::Figure fig;
	//	D1.add_to_figure(fig);
	//	gr::Animation_canvas canvas;
	//	canvas.display_figure(fig);
	//
	//
	//	std::cout << "DCEL is" << (D1.is_valid() ? "" : " NOT")
	//			  << " valid" << std::endl;
	//
	//	return;

	unsigned nb_vertices = D1.vertices.size();

	test(D1, D1.vertices[nb_vertices - 1], D1.vertices[nb_vertices - 2]);

	DCEL D2 = geo::load_DCEL(file);
	test(D2, D2.vertices[nb_vertices - 2], D2.vertices[nb_vertices - 1]);
}

int main()
{
	std::cout << "test 1 ..." << std::endl;
	test("unit_test_input/add_diagonal_test1");
	std::cout << std::endl;

	std::cout << "test 2 ..." << std::endl;
	test("unit_test_input/add_diagonal_test2");
	std::cout << std::endl;

	std::cout << "test 3 ..." << std::endl;
	test("unit_test_input/add_diagonal_test3");
	std::cout << std::endl;
}