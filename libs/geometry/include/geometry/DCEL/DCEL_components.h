#pragma once

#include <memory>
#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>


namespace geometry::DCEL
{
	typedef boost::rational<boost::multiprecision::cpp_int> rational;

	struct Vertex;
	struct Hedge;
	struct Face;

	typedef std::shared_ptr<Vertex> Vertex_ptr;
	typedef std::shared_ptr<Hedge> Hedge_ptr;
	typedef std::shared_ptr<Face> Face_ptr;

	struct Vertex
	{
		rational x;
		rational y;
		Hedge_ptr inc_edge;
	};

	struct Hedge
	{
		Vertex_ptr origin;
		Hedge_ptr prev;
		Hedge_ptr next;
		Hedge_ptr twin;
		Face_ptr inc_face;
	};

	struct Face
	{
		Hedge_ptr inner_comp;
		Hedge_ptr outer_comp;
	};
}
