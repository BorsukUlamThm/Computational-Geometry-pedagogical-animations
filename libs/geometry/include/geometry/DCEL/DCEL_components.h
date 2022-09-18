#pragma once

#include "geometry/DCEL/DCEL.h"


namespace geometry
{
	struct DCEL::Vertex
	{
		real x;
		real y;
		Hedge* inc_edge = nullptr;

		Vertex() = default;
		Vertex(const real& x,
			   const real& y,
			   Hedge* inc_edge = nullptr);
		~Vertex() = default;
	};

	struct DCEL::Hedge
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

	struct DCEL::Face
	{
		std::vector<Hedge*> inner_comp {};
		Hedge* outer_comp = nullptr;

		Face() = default;
		Face(std::vector<Hedge*> inner_comp,
			 Hedge* outer_comp);
		~Face() = default;
	};
}
