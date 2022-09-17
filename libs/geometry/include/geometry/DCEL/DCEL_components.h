#pragma once

#include "geometry/model/real.h"


namespace geometry::DCEL
{
	struct Vertex;
	struct Hedge;
	struct Face;

	struct Vertex
	{
		real x;
		real y;
		Hedge* inc_edge = nullptr;

		Vertex() = default;
		Vertex(real x,
			   real y,
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
		std::vector<Hedge*> inner_comp {};
		Hedge* outer_comp = nullptr;

		Face() = default;
		Face(std::vector<Hedge*> inner_comp,
			 Hedge* outer_comp);
		~Face() = default;
	};
}
