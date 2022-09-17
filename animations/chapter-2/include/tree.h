#pragma once

#include "utils.h"
#include "geometry/utils/AVL.h"
#include "graphics/model/Animation.h"


namespace segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	struct event;

	struct tree_cmp
	{
		point p {};
		bool just_above = true;
		segment_set& S;

		explicit tree_cmp(segment_set& S);

		bool operator()(unsigned i, unsigned j) const;
		bool are_equal(unsigned i, unsigned j) const;
	};

	class tree : public geo::AVL_tree<unsigned, tree_cmp>
	{
		typedef geo::AVL_tree<unsigned, tree_cmp> super;

	public:
		explicit tree(const tree_cmp& comp);

		unsigned left_neighbour(const point& p);
		unsigned right_neighbour(const point& p);

		void plot(gr::Animation* animation);

	private:
		unsigned aux_left_neighbour(const point& p,
									Node* node,
									Node* candidate) const;
		unsigned aux_right_neighbour(const point& p,
									 Node* node,
									 Node* candidate) const;
		unsigned aux_plot(gr::Animation* animation,
						  tree::Node* node,
						  unsigned min);
	};
}