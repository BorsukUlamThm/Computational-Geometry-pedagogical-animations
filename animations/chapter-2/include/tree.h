#pragma once

#include "utils.h"
#include "geometry/utils/AVL.h"
#include "graphics/model/Animation.h"


namespace segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	class tree : public geo::AVL_tree<unsigned>
	{
		typedef geo::AVL_tree<unsigned> super;

	private:
		point event_p {};
		bool just_above = true;
		segment_set& S;

	public:
		explicit tree(segment_set& S);

		void set_comparison_just_above();
		void set_comparison_just_below();
		void set_event_p(const point& p);

		segment get_ith_segment(unsigned i);

		unsigned left_neighbour(const point& p);
		unsigned right_neighbour(const point& p);

		void plot(gr::Animation* animation);

		bool compare(const unsigned& i,
					 const unsigned& j) const override;
		bool are_equal(const unsigned& i,
					   const unsigned& j) const override;

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