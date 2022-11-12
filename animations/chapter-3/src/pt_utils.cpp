#include "../include/pt_utils.h"
#include "utils/Program_options.h"
#include "graphics/view/Acquisition_canvas.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/algorithms/segment_intersections.h"


namespace polygon_triangulation
{
	Options process_command_line(int argc,
								 char** argv)
	{
		Options opt;
		utils::Program_options program_options;

		enum Options
		{
			INPUT_FILE_OPT,
			ACQUISITION_OPT
		};

		program_options.add_option("input_file", "i");
		program_options.add_option("acquisition", "a");
		program_options.parse_command_line(argc, argv);

		if (program_options[INPUT_FILE_OPT].is_used)
		{
			opt.input_type = FILE;
			if (program_options[INPUT_FILE_OPT].parameters.empty())
			{
				std::cerr << "[options] "
						  << "invalid --input_file -i parameter, "
						  << "missing input file"
						  << std::endl;
			}
			else
			{
				opt.input_file = program_options[INPUT_FILE_OPT].parameters[0];
			}
		}
		if (program_options[ACQUISITION_OPT].is_used)
		{
			opt.input_type = ACQUISITION;
		}

		std::cout << std::endl
				  << "input type : ";
		switch (opt.input_type)
		{
			case FILE:
				std::cout << "file ("
						  << opt.input_file
						  << ")";
				break;
			case ACQUISITION:
				std::cout << "acquisition";
				break;
		}
		std::cout << std::endl << std::endl;

		return opt;
	}

	DCEL make_polygon(const Options& opt)
	{
		if (opt.input_type == ACQUISITION)
		{
			gr::Acquisition_canvas canvas;
			canvas.set_title("Polygon Triangulation - acquisition");
			canvas.add_polygon_acquisition();
			gr::Acquisitions acquisitions = canvas.acquire_buffer();

			std::vector<geo::segment_2> edges;
			for (auto& face : acquisitions[0]->get_objects<gr::Polygon_obj>())
			{
				for (unsigned i = 0; i < face.size(); ++i)
				{
					geo::point_2 v1(face[i].abscissa,
									face[i].ordinate);
					geo::point_2 v2(face[(i + 1) % face.size()].abscissa,
									face[(i + 1) % face.size()].ordinate);
					edges.emplace_back(v1, v2);
				}
			}

			return segment_intersections(edges);
		}

		return geo::load_DCEL(opt.input_file);
	}

	face* get_main_face(const DCEL& D)
	{ return D.get_unbounded_face()->inner_comp[0]->twin->inc_face; }

	bool is_valid(const DCEL& D)
	{
		for (auto& f : D.faces)
		{
			if (f->outer_comp == nullptr)
			{
				if (f->inner_comp.size() != 1)
				{
					std::cout << "Error : polygon has more than one"
							  << " connected component"
							  << std::endl;
					return false;
				}
			}
			else if (f->outer_comp->twin->inc_face->outer_comp == nullptr)
			{
				continue;
			}
			else
			{
				if (!f->inner_comp.empty())
				{
					std::cout << "Error : polygon has more than one"
							  << " connected component"
							  << std::endl;
					return false;
				}
			}
		}

		for (auto& v : D.vertices)
		{
			if (v->degree() != 2)
			{
				std::cout << "Error : polygon is not simple" << std::endl;
				return false;
			}
		}

		return true;
	}

	void plot_monotone_face(face* f,
							gr::Animation& animation)
	{
		hedge* h = f->outer_comp;
		do
		{
			gr::Coordinate x1(h->origin->x);
			gr::Coordinate y1(h->origin->y);
			gr::Coordinate x2(h->twin->origin->x);
			gr::Coordinate y2(h->twin->origin->y);

			animation[MONOTONE_FACE].add_segment(x1, y1, x2, y2, gr::RED);
			h = h->next;
		}
		while (h != f->outer_comp);
	}

	void plot_polygon(DCEL& D,
					  gr::Animation& animation)
	{
		DCEL::mark_t treated = D.get_new_mark();

		for (auto& h : D.half_edges)
		{
			if (h->twin->is_marked(treated))
			{ continue; }

			gr::Coordinate x1(h->origin->x);
			gr::Coordinate y1(h->origin->y);
			gr::Coordinate x2(h->twin->origin->x);
			gr::Coordinate y2(h->twin->origin->y);

			animation[POLYGON].add_segment(x1, y1, x2, y2);

			h->mark(treated);
		}
		animation.make_new_frame();

		D.free_mark(treated);
	}

	struct vertices_cmp
	{
		bool operator()(vertex* v1, vertex* v2)
		{
			point p1(v1->x, v1->y);
			point p2(v2->x, v2->y);
			return geo::point_above_point(p1, p2);
		}
	};

	void push_boundary(queue& Q, hedge* h)
	{
		hedge* it = h;
		do
		{
			it->origin->inc_edge = it;
			Q.push_back(it->origin);
			it = it->next;
		}
		while (it != h);
	}

	queue init_Q_and_inc_edges(face* f)
	{
		queue Q;
		push_boundary(Q, f->outer_comp);
		for (auto& h : f->inner_comp)
		{ push_boundary(Q, h); }

		vertices_cmp cmp;
		std::sort(Q.begin(), Q.end(), cmp);

		return Q;
	}

	void add_diagonal(vertex* v1,
					  vertex* v2,
					  std::vector<diagonal>& diags,
					  gr::Animation& animation)
	{
		diags.emplace_back(v1, v2);

		gr::Coordinate x1(v1->x);
		gr::Coordinate y1(v1->y);
		gr::Coordinate x2(v2->x);
		gr::Coordinate y2(v2->y);

		animation[POLYGON].add_segment(x1, y1, x2, y2, gr::YELLOW);
		animation.make_new_frame();
	}

	std::vector<face*> cut_along_diagonals(DCEL& D,
										   const std::vector<diagonal>& diags)
	{
		std::vector<hedge*> diagonal_hedges;

		if (diags.empty())
		{
			hedge* h = D.get_unbounded_face()->inner_comp[0]->twin;
			diagonal_hedges.push_back(h);
		}
		else
		{
			for (auto& d : diags)
			{
				D.add_diagonal(d.ogn, d.dst);
				diagonal_hedges.push_back(
						D.half_edges[D.half_edges.size() - 1]);
				diagonal_hedges.push_back(
						D.half_edges[D.half_edges.size() - 2]);
			}
		}

		std::vector<face*> faces;
		DCEL::mark_t treated = D.get_new_mark();
		for (auto& h : diagonal_hedges)
		{
			if (h->is_marked(treated))
			{ continue; }

			auto* f = new face();
			f->outer_comp = h;
			D.faces.push_back(f);
			faces.push_back(f);

			hedge* it = h;
			do
			{
				it->mark(treated);
				it->inc_face = f;
				it = it->next;
			}
			while (it != h);
		}

		D.free_mark(treated);
		return faces;
	}
}