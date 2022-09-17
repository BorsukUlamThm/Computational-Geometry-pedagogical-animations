#include "../include/tree.h"
#include "geometry/utils/line_intersections.h"
#include "geometry/utils/point_comparisons.h"


namespace segment_intersections
{
	tree_cmp::tree_cmp(segment_set& S) :
			S(S)
	{}

	bool tree_cmp::operator()(unsigned i, unsigned j) const
	{
		if (i == j)
		{
			return true;
		}

		geo::real xi = (S[i].p1.y == S[i].p2.y ?
						p.x : geo::x_intersection(S[i], p.y));
		geo::real xj = (S[j].p1.y == S[j].p2.y ?
						p.x : geo::x_intersection(S[j], p.y));
		if (xi == xj)
		{
			point center(xi, p.y);

			if (just_above)
			{
				point pi = (S[i].p1 != center ? S[i].p1 : S[i].p2);
				pi = (geo::point_above_point(pi, center) ?
					  pi : center + center - pi);
				point pj = (S[j].p1 != center ? S[j].p1 : S[j].p2);
				pj = (geo::point_above_point(pj, center) ?
					  pj : center + center - pj);
				return geo::point_left_line(pi, center, pj);
			}

			point pi = (S[i].p1 != center ? S[i].p1 : S[i].p2);
			pi = (geo::point_below_point(pi, center) ?
				  pi : center + center - pi);
			point pj = (S[j].p1 != center ? S[j].p1 : S[j].p2);
			pj = (geo::point_below_point(pj, center) ?
				  pj : center + center - pj);

			return geo::point_left_line(pi, pj, center);
		}

		return xi < xj;
	}

	bool tree_cmp::are_equal(unsigned int i, unsigned int j) const
	{ return i == j; }

	tree::tree(const tree_cmp& comp) :
			super(comp)
	{}

	unsigned tree::left_neighbour(const point& p)
	{ return aux_left_neighbour(p, root, nullptr); }

	unsigned tree::right_neighbour(const point& p)
	{ return aux_right_neighbour(p, root, nullptr); }

	unsigned tree::aux_left_neighbour(const point& p,
									  geo::AVL_node<unsigned>* node,
									  geo::AVL_node<unsigned>* candidate) const
	{
		if (node == nullptr)
		{ return candidate == nullptr ? -1 : candidate->root; }

		geo::real x = geo::x_intersection(comp.S[node->root], p.y);
		if (p.x < x)
		{
			return aux_left_neighbour(p, node->left, candidate);
		}
		return aux_left_neighbour(p, node->right, node);
	}

	unsigned tree::aux_right_neighbour(const point& p,
									   geo::AVL_node<unsigned>* node,
									   geo::AVL_node<unsigned>* candidate) const
	{
		if (node == nullptr)
		{ return candidate == nullptr ? -1 : candidate->root; }

		geo::real x = geo::x_intersection(comp.S[node->root], p.y);
		if (p.x < x)
		{
			return aux_right_neighbour(p, node->left, node);
		}
		return aux_right_neighbour(p, node->right, candidate);
	}

	void tree::plot(gr::Animation* animation)
	{
		if (root == nullptr)
		{ return; }

		animation->get(TREE).clear();
		aux_plot(animation, root, 0);
		animation->make_new_frame();
	}

	unsigned tree::aux_plot(gr::Animation* animation,
							tree::Node* node,
							unsigned min)
	{
		if (node == nullptr)
		{ return min; }

		unsigned max = aux_plot(animation, node->left, min);

		segment s = comp.S[node->root];
		float x1(s.p1.x);
		float y1(s.p1.y);
		float x2(s.p2.x);
		float y2(s.p2.y);
		gr::Point_shp p(x1, y1);

		animation->get(TREE).add_segment(x1, y1, x2, y2, gr::RED);
		std::string index = std::to_string(max);
		animation->get(TREE).add_text(index, p, 16, gr::RED);

		return aux_plot(animation, node->right, max + 1);
	}
}