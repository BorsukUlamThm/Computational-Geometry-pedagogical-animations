#include "../include/monotone_partition.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/line_intersections.h"


namespace polygon_triangulation
{
	type_marks::type_marks(DCEL& D)
	{
		start = D.get_new_mark();
		end = D.get_new_mark();
		split = D.get_new_mark();
		merge = D.get_new_mark();
		regular = D.get_new_mark();
	}

	DCEL::mark_t make_type(hedge* h,
						   type_marks types)
	{
		point p(h->prev->origin->x, h->prev->origin->y);
		point q(h->origin->x, h->origin->y);
		point r(h->next->origin->x, h->next->origin->y);

		if (geo::point_above_point(p, q))
		{
			if (geo::point_above_point(q, r))
			{ return types.regular; }
			if (geo::point_right_line(p, q, r))
			{ return types.merge; }
			return types.end;
		}
		if (geo::point_above_point(r, q))
		{ return types.regular; }
		if (geo::point_right_line(p, q, r))
		{ return types.split; }
		return types.start;
	}

	type_marks make_type_map(DCEL& D)
	{
		type_marks types(D);
		face* f = D.get_unbounded_face()->inner_comp[0]->twin->inc_face;

		hedge* it_end = f->outer_comp;
		hedge* it = it_end;
		do
		{
			it->origin->mark(make_type(it, types));
			it = it->next;
		}
		while (it != it_end);

		for (auto& h : f->inner_comp)
		{
			it = h;
			do
			{
				it->origin->mark(make_type(it, types));
				it = it->next;
			}
			while (it != h);
		}
		return types;
	}

	void plot_type(vertex* v,
				   const type_marks& types,
				   gr::Animation& animation)
	{
		gr::Coordinate x(v->x);
		gr::Coordinate y(v->y);
		gr::Point_shp p(x, y);
		std::string name;

		if (v->is_marked(types.start))
		{ name = "start"; }
		else if (v->is_marked(types.end))
		{ name = "end"; }
		else if (v->is_marked(types.split))
		{ name = "split"; }
		else if (v->is_marked(types.merge))
		{ name = "merge"; }
		else if (v->is_marked(types.regular))
		{ name = "regular"; }
		else
		{ name = "TYPE NOT FOUND !!!"; }

		animation[TYPES].add_text(name, p, 16, gr::YELLOW);
	}

	bool tree::compare(hedge* const& h1,
					   hedge* const& h2) const
	{
		point p(h1->origin->x, h1->origin->y);
		point q(h1->twin->origin->x, h1->twin->origin->y);
		if (geo::point_below_point(p, q))
		{ return compare(h1->twin, h2); }

		p = point(h2->origin->x, h2->origin->y);
		q = point(h2->twin->origin->x, h2->twin->origin->y);
		if (geo::point_below_point(p, q))
		{ return compare(h1, h2->twin); }

		point u1(h1->origin->x, h1->origin->y);
		point u2(h2->origin->x, h2->origin->y);
		point d1(h1->twin->origin->x, h1->twin->origin->y);
		point d2(h2->twin->origin->x, h2->twin->origin->y);

		if (geo::point_above_point(u1, u2))
		{ return geo::point_left_line(u2, u1, d1); }
		return geo::point_right_line(u1, u2, d2);
	}

	bool tree::are_equal(hedge* const& h1,
						 hedge* const& h2) const
	{ return h1 == h2; }

	void tree::plot(helper_map& helpers,
					gr::Animation& animation)
	{
		animation[TREE].clear();
		aux_plot(root, helpers, animation, 0);
	}

	hedge* tree::left_neighbour(vertex* v) const
	{ return aux_left_neighbour(v, root, nullptr); }

	hedge* tree::aux_left_neighbour(vertex* v,
									tree::Node* node,
									hedge* candidate) const
	{
		if (node == nullptr)
		{ return candidate; }

		if (geo::point_left_line(v, node->root))
		{
			return aux_left_neighbour(v, node->right, node->root);
		}
		return aux_left_neighbour(v, node->left, candidate);
	}

	unsigned tree::aux_plot(tree::Node* node,
							helper_map& helpers,
							gr::Animation& animation,
							unsigned min)
	{
		if (node == nullptr)
		{ return min; }

		unsigned max = aux_plot(node->left, helpers, animation, min);

		gr::Coordinate x1(node->root->origin->x);
		gr::Coordinate y1(node->root->origin->y);
		gr::Coordinate x2(node->root->twin->origin->x);
		gr::Coordinate y2(node->root->twin->origin->y);
		gr::Coordinate xh(helpers[node->root]->x);
		gr::Coordinate yh(helpers[node->root]->y);
		gr::Point_shp h(xh, yh);
		gr::Coordinate x_inter(geo::x_intersection(node->root, yh));
		gr::Segment_obj s(x1, y1, x2, y2);
		gr::Segment_obj s_helper(x_inter, yh, xh, yh);

		animation[TREE].add_vector(x_inter, yh, xh, yh, gr::BLUE);
		animation[TREE].add_text("helper", s_helper, 16, gr::BLUE);
		animation[TREE].add_segment(x1, y1, x2, y2, gr::RED);
		animation[TREE].add_text(std::to_string(max), s, 16, gr::RED);

		return aux_plot(node->right, helpers, animation, max + 1);
	}

	void handle_start_vertex(vertex* v,
							 tree& T,
							 helper_map& helpers,
							 gr::Animation& animation)
	{
		T.insert(v->inc_edge);
		helpers[v->inc_edge] = v;

		T.plot(helpers, animation);
		animation.make_new_frame();
	}

	void handle_end_vertex(vertex* v,
						   type_marks& types,
						   tree& T,
						   helper_map& helpers,
						   std::vector<diagonal>& diags,
						   gr::Animation& animation)
	{
		if (helpers[v->inc_edge->prev]->is_marked(types.merge))
		{
			add_diagonal(v, helpers[v->inc_edge->prev], diags, animation);
		}
		T.remove(v->inc_edge->prev);

		T.plot(helpers, animation);
		animation.make_new_frame();
	}

	void handle_split_vertex(vertex* v,
							 tree& T,
							 helper_map& helpers,
							 std::vector<diagonal>& diags,
							 gr::Animation& animation)
	{
		hedge* h = T.left_neighbour(v);
		add_diagonal(v, helpers[h], diags, animation);

		helpers[h] = v;
		T.insert(v->inc_edge);
		helpers[v->inc_edge] = v;

		T.plot(helpers, animation);
		animation.make_new_frame();
	}

	void handle_merge_vertex(vertex* v,
							 type_marks& types,
							 tree& T,
							 helper_map& helpers,
							 std::vector<diagonal>& diags,
							 gr::Animation& animation)
	{
		if (helpers[v->inc_edge->prev]->is_marked(types.merge))
		{
			add_diagonal(v, helpers[v->inc_edge->prev], diags, animation);
		}
		T.remove(v->inc_edge->prev);

		T.plot(helpers, animation);
		animation.make_new_frame();

		hedge* h = T.left_neighbour(v);
		if (helpers[h]->is_marked(types.merge))
		{
			add_diagonal(v, helpers[h], diags, animation);
		}

		helpers[h] = v;
		T.plot(helpers, animation);
		animation.make_new_frame();
	}

	void handle_regular_vertex(vertex* v,
							   type_marks& types,
							   tree& T,
							   helper_map& helpers,
							   std::vector<diagonal>& diags,
							   gr::Animation& animation)
	{
		point p(v->x, v->y);
		point q(v->inc_edge->next->origin->x, v->inc_edge->next->origin->y);

		if (geo::point_above_point(p, q))
		{
			if (helpers[v->inc_edge->prev]->is_marked(types.merge))
			{
				add_diagonal(v, helpers[v->inc_edge->prev], diags, animation);
			}
			T.remove(v->inc_edge->prev);

			T.plot(helpers, animation);
			animation.make_new_frame();

			T.insert(v->inc_edge);
			helpers[v->inc_edge] = v;

			T.plot(helpers, animation);
			animation.make_new_frame();
		}
		else
		{
			hedge* h = T.left_neighbour(v);
			if (helpers[h]->is_marked(types.merge))
			{
				add_diagonal(v, helpers[h], diags, animation);
			}

			helpers[h] = v;
			T.plot(helpers, animation);
			animation.make_new_frame();
		}
	}

	std::vector<face*> make_monotone(DCEL& D,
									 gr::Animation& animation)
	{
		type_marks types = make_type_map(D);
		animation.make_new_frame();

		tree T;
		helper_map helpers;
		queue Q = init_Q_and_inc_edges(get_main_face(D));
		std::vector<diagonal> diags;

		D.delete_face(get_main_face(D));
		for (auto& v : Q)
		{
			animation[LINE].clear();
			animation[LINE].add_horizontal_line(gr::Coordinate(v->y));
			plot_type(v, types, animation);
			animation.make_new_frame();

			if (v->is_marked(types.start))
			{ handle_start_vertex(v, T, helpers, animation); }
			else if (v->is_marked(types.end))
			{ handle_end_vertex(v, types, T, helpers, diags, animation); }
			else if (v->is_marked(types.split))
			{ handle_split_vertex(v, T, helpers, diags, animation); }
			else if (v->is_marked(types.merge))
			{ handle_merge_vertex(v, types, T, helpers, diags, animation); }
			else if (v->is_marked(types.regular))
			{ handle_regular_vertex(v, types, T, helpers, diags, animation); }
			else
			{ std::cerr << "TYPE NOT FOUND"; }

			if (!v->is_marked(types.merge))
			{ animation[TYPES].erase_last_shape(); }
		}

		animation[TYPES].clear();
		animation[LINE].clear();
		animation.make_new_frame();

		return cut_along_diagonals(D, diags);
	}
}