#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include <vector>
#include <iostream>


namespace geometry
{
	struct DCEL
	{
		struct vertex;
		struct hedge;
		struct face;

		std::vector<vertex*> vertices {};
		std::vector<hedge*> half_edges {};
		std::vector<face*> faces {};

		DCEL() = default;
		~DCEL();

		enum is_valid_check
		{
			VERTICES_CHECK = 1,
			HEDGES_CHECK   = 2,
			FACES_CHECK    = 4,
			OVERLAP_CHECK  = 8,
			ALL_CHECK      = 15, // last one * 2 - 1
		};

		bool is_valid(unsigned mask = ALL_CHECK);
		void clear();

		void delete_vertex(vertex* v);
		void delete_hedge(hedge* h);
		void delete_face(face* f);

	private:
		bool vertices_check();
		bool hedges_check();
		bool faces_check();
		bool overlap_check();

	public:
		friend std::ostream& operator<<(std::ostream& os,
										const DCEL& D);
	};

	struct DCEL::vertex
	{
		real x;
		real y;
		hedge* inc_edge = nullptr;

		vertex() = default;
		vertex(const real& x,
			   const real& y,
			   hedge* inc_edge = nullptr);
		~vertex() = default;
	};

	struct DCEL::hedge
	{
		vertex* origin = nullptr;
		hedge* prev = nullptr;
		hedge* next = nullptr;
		hedge* twin = nullptr;
		face* inc_face = nullptr;

		hedge() = default;
		hedge(vertex* origin,
			  hedge* prev,
			  hedge* next,
			  hedge* twin,
			  face* inc_face);
		~hedge() = default;
	};

	struct DCEL::face
	{
		std::vector<hedge*> inner_comp {};
		hedge* outer_comp = nullptr;

		face() = default;
		face(std::vector<hedge*> inner_comp,
			 hedge* outer_comp);
		~face() = default;
	};

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& D);
}