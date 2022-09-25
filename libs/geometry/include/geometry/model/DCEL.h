#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include <vector>
#include <iostream>


namespace geometry
{
	struct DCEL
	{
		struct Vertex;
		struct Hedge;
		struct Face;

		std::vector<Vertex*> vertices {};
		std::vector<Hedge*> half_edges {};
		std::vector<Face*> faces {};

		DCEL() = default;
		~DCEL();

		bool is_valid();
		void clear();

		friend std::ostream& operator<<(std::ostream& os,
										const DCEL& dcel);
	};

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

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& dcel);
}