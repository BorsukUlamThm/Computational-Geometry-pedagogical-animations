#include "segment_intersections/tree.h"
#include "geometry/utils/line_intersections.h"


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

		rational xi = geo::x_intersection(S[i], y_line);
		rational xj = geo::x_intersection(S[j], y_line);
		if (xi == xj)
		{
			point center(xi, y_line);

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

		rational x = geo::x_intersection(comp.S[node->root], p.y);
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

		rational x = geo::x_intersection(comp.S[node->root], p.y);
		if (p.x < x)
		{
			return aux_right_neighbour(p, node->left, node);
		}
		return aux_right_neighbour(p, node->right, candidate);
	}
}