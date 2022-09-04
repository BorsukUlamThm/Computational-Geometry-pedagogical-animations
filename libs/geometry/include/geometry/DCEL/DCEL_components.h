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

	struct Vertex
	{
		rational x;
		rational y;
		Hedge* inc_edge = nullptr;

		Vertex() = default;
		Vertex(rational x,
			   rational y,
			   Hedge* inc_edge = nullptr);
		~Vertex() = default;
	};

	struct Hedge
	{
		Vertex* origin = nullptr;
		Hedge* prev = nullptr;
		Hedge* next = nullptr;
		Hedge* twin = nullptr;
		Face* inc_face = nullptr;

		Hedge() = default;
		Hedge(Vertex* origin,
			  Hedge* prev,
			  Hedge* next,
			  Hedge* twin,
			  Face* inc_face);
		~Hedge() = default;
	};

	struct Face
	{
		Hedge* inner_comp = nullptr;
		Hedge* outer_comp = nullptr;

		Face() = default;
		Face(Hedge* inner_comp,
			 Hedge* outer_comp);
		~Face() = default;
	};
}
