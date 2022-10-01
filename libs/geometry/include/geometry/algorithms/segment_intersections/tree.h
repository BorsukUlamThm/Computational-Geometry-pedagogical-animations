#pragma once

#include "utils.h"
#include "geometry/utils/AVL.h"
#include "graphics/view/Animation_canvas.h"


namespace gr = graphics;

namespace geometry::segment_intersections_components
{
	class tree : public AVL_tree<hedge*>
	{
	public:
		typedef AVL_node<hedge*> Node;

	public:
		point_2 event_p {};
		bool just_above = true;

		gr::Animation animation = gr::Animation(4);

	public:
		tree() = default;

		void set_comparison_just_above();
		void set_comparison_just_below();
		void set_event_p(const point_2& p);

		hedge* left_neighbour(const point_2& p);
		hedge* right_neighbour(const point_2& p);

		bool compare(hedge* const& h1,
					 hedge* const& h2) const override;
		bool are_equal(hedge* const& h1,
					   hedge* const& h2) const override;

		void plot();
		void plot_segments(const std::vector<segment_2>& S);
		void plot_point(const point_2& p);

	private:
		hedge* aux_left_neighbour(const point_2& p,
								  Node* node,
								  Node* candidate) const;
		hedge* aux_right_neighbour(const point_2& p,
								   Node* node,
								   Node* candidate) const;
		unsigned aux_plot(Node* node,
						  unsigned min);
	};
}