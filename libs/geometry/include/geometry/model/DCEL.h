#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include "graphics/model/Figure.h"
#include <vector>
#include <iostream>


namespace geometry
{
	struct DCEL
	{
		struct component;
		struct vertex;
		struct hedge;
		struct face;

		typedef unsigned mark_t;
		static constexpr unsigned MAX_MARKS =
				std::numeric_limits<mark_t>::digits;

		std::vector<vertex*> vertices {};
		std::vector<hedge*> half_edges {};
		std::vector<face*> faces {};

		mark_t used_marks = 0;

		DCEL() = default;
		~DCEL();

		enum is_valid_check
		{
			VERTICES_CHECK = 1,
			HEDGES_CHECK = 2,
			FACES_CHECK = 4,
			INTERSECTION_CHECK = 8,
			ALL_CHECK = 15, // last one * 2 - 1
		};
		bool is_valid(unsigned mask = ALL_CHECK);

		void add_diagonal(vertex* v1,
						  vertex* v2); //doesn't handle the new created face !!
		void clear();

		face* get_unbounded_face() const;

		mark_t get_new_mark();
		void free_mark(mark_t m);

		void delete_vertex(vertex* v);
		void delete_hedge(hedge* h);
		void delete_face(face* f);

		void add_to_figure(gr::Figure& fig);

	private:
		bool vertices_check();
		bool hedges_check();
		bool faces_check();
		bool intersection_check() const;
	};

	struct DCEL::component
	{
		mark_t marks = 0;

		void mark(mark_t m);
		void unmark(mark_t m);
		bool is_marked(mark_t m) const;
	};

	struct DCEL::vertex : public DCEL::component
	{
		real x;
		real y;
		hedge* inc_edge = nullptr;

		vertex() = default;
		vertex(const real& x,
			   const real& y,
			   hedge* inc_edge = nullptr);
		~vertex() = default;

		unsigned degree() const;
		void add_to_figure(gr::Figure& fig,
						   gr::Color col = gr::DEFAULT_SHAPE_COLOR);
	};

	struct DCEL::hedge : public DCEL::component
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

		void add_to_figure(gr::Figure& fig,
						   gr::Color col = gr::DEFAULT_SHAPE_COLOR);
	};

	struct DCEL::face : public DCEL::component
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