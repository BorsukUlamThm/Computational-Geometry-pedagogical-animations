#include "geometry/algorithms/segment_intersections/tree.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/line_intersections.h"


namespace geometry::segment_intersections_components
{
	void tree::set_comparison_just_above()
	{ just_above = true; }

	void tree::set_comparison_just_below()
	{ just_above = false; }

	void tree::set_event_p(const point_2& p)
	{ event_p = p; }

	hedge* tree::left_neighbour(const point_2& p)
	{ return aux_left_neighbour(p, root, nullptr); }

	hedge* tree::right_neighbour(const point_2& p)
	{ return aux_right_neighbour(p, root, nullptr); }

	bool tree::compare(hedge* const& h1,
					   hedge* const& h2) const
	{
		if (h1 == h2)
		{ return true; }

		point_2 h1p1(h1->origin->x, h1->origin->y);
		point_2 h1p2(h1->twin->origin->x, h1->twin->origin->y);
		point_2 h2p1(h2->origin->x, h2->origin->y);
		point_2 h2p2(h2->twin->origin->x, h2->twin->origin->y);

		real x1 = (h1p1.y == h1p2.y ?
				   event_p.x : x_intersection(h1, event_p.y));
		real x2 = (h2p1.y == h2p2.y ?
				   event_p.x : x_intersection(h2, event_p.y));
		if (x1 == x2)
		{
			point_2 center(x1, event_p.y);

			if (just_above)
			{
				point_2 pi = (h1p1 != center ? h1p1 : h1p2);
				pi = (point_above_point(pi, center) ?
					  pi : center + center - pi);
				point_2 pj = (h2p1 != center ? h2p1 : h2p2);
				pj = (point_above_point(pj, center) ?
					  pj : center + center - pj);

				return point_left_line(pi, center, pj);
			}

			point_2 pi = (h1p1 != center ? h1p1 : h1p2);
			pi = (point_below_point(pi, center) ?
				  pi : center + center - pi);
			point_2 pj = (h2p1 != center ? h2p1 : h2p2);
			pj = (point_below_point(pj, center) ?
				  pj : center + center - pj);

			return point_left_line(pi, pj, center);
		}

		return x1 < x2;
	}

	bool tree::are_equal(hedge* const& h1,
						 hedge* const& h2) const
	{ return h1 == h2; }

	void tree::plot()
	{
		if (root == nullptr)
		{ return; }

		animation[1].clear();
		aux_plot(root, 0);
		animation.make_new_frame();
	}

	void tree::plot_segments(const std::vector<segment_2>& S)
	{
		for (auto& s : S)
		{
			gr::Coordinate x1(s.p1.x);
			gr::Coordinate y1(s.p1.y);
			gr::Coordinate x2(s.p2.x);
			gr::Coordinate y2(s.p2.y);

			animation[0].add_segment(x1, y1, x2, y2);
		}
	}

	void tree::plot_point(const geometry::point_2& p)
	{
		gr::Coordinate x(p.x);
		gr::Coordinate y(p.y);

		std::string coord = std::to_string(p.x.approx);
		coord += " ";
		coord += std::to_string(p.y.approx);

		gr::Point_shp pt(x, y);

		animation[2].clear();
		animation[2].add_point(x, y, gr::GREEN);
		animation[2].add_text(coord, pt, 16, gr::GREEN);
		animation[2].add_horizontal_line(y);
		animation.make_new_frame();
	}

	hedge* tree::aux_left_neighbour(const point_2& p,
									Node* node,
									Node* candidate) const
	{
		if (node == nullptr)
		{ return candidate == nullptr ? nullptr : candidate->root; }

		real x = x_intersection(node->root, p.y);
		if (p.x < x)
		{
			return aux_left_neighbour(p, node->left, candidate);
		}
		return aux_left_neighbour(p, node->right, node);
	}

	hedge* tree::aux_right_neighbour(const point_2& p,
									 Node* node,
									 Node* candidate) const
	{
		if (node == nullptr)
		{ return candidate == nullptr ? nullptr : candidate->root; }

		real x = x_intersection(node->root, p.y);
		if (p.x < x)
		{
			return aux_right_neighbour(p, node->left, node);
		}
		return aux_right_neighbour(p, node->right, candidate);
	}

	unsigned tree::aux_plot(Node* node,
							unsigned min)
	{
		if (node == nullptr)
		{ return min; }

		unsigned max = aux_plot(node->left, min);

		float x1(node->root->origin->x);
		float y1(node->root->origin->y);
		float x2(node->root->twin->origin->x);
		float y2(node->root->twin->origin->y);
		gr::Point_shp p1(x1, y1);
		gr::Point_shp p2(x2, y2);

		animation[1].add_segment(x1, y1, x2, y2, gr::RED);
		std::string index = std::to_string(max);
		animation[1].add_text(index, p1, 16, gr::RED);
		animation[1].add_text(index, p2, 16, gr::RED);

		return aux_plot(node->right, max + 1);
	}
}