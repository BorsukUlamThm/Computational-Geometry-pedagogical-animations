#pragma once

#include "geometry/model/DCEL.h"
#include "geometry/utils/random_generation.h"
#include "graphics/view/Animation_canvas.h"


namespace polygon_triangulation
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef geo::point_2 point;
	typedef geo::DCEL DCEL;
	typedef DCEL::vertex vertex;
	typedef DCEL::hedge hedge;
	typedef DCEL::face face;
	typedef std::vector<vertex*> queue;

	enum Figures
	{
		LINE,
		POLYGON,
		MONOTONE_FACE,
		TYPES,
		TREE,
		STACK,
		NB_FIGURES
	};

	enum Input_type
	{
		ACQUISITION,
		FILE
	};

	struct Options
	{
		Input_type input_type = ACQUISITION;
		std::string input_file {};
	};

	Options process_command_line(int argc,
								 char** argv);

	DCEL make_polygon(const Options& opt);

	face* get_main_face(const DCEL& D);

	bool is_valid(const DCEL& D);

	void plot_monotone_face(face* f,
							gr::Animation& animation);

	void plot_polygon(DCEL& D,
					  gr::Animation& animation);

	queue init_Q_and_inc_edges(face* f);

	struct diagonal
	{
		vertex* ogn;
		vertex* dst;

		diagonal(vertex* ogn,
				 vertex* dst) :
				ogn(ogn),
				dst(dst)
		{}
	};

	void add_diagonal(vertex* v1,
					  vertex* v2,
					  std::vector<diagonal>& diags,
					  gr::Animation& animation);

	std::vector<face*> cut_along_diagonals(DCEL& D,
										   const std::vector<diagonal>& diags);
}