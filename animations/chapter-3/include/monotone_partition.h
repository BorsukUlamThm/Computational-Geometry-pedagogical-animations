#pragma once

#include "pt_utils.h"
#include "geometry/utils/AVL.h"
#include <map>


namespace polygon_triangulation
{
	typedef std::map<hedge*, vertex*> helper_map;

	struct type_marks
	{
		DCEL::mark_t start = 0;
		DCEL::mark_t end = 0;
		DCEL::mark_t split = 0;
		DCEL::mark_t merge = 0;
		DCEL::mark_t regular = 0;

		explicit type_marks(DCEL& D);
	};

	type_marks make_type_map(DCEL& D);

	class tree : public geo::AVL_tree<hedge*>
	{
	public:
		typedef geo::AVL_node<hedge*> Node;

		tree() = default;

		bool compare(hedge* const& h1,
					 hedge* const& h2) const override;
		bool are_equal(hedge* const& h1,
					   hedge* const& h2) const override;

		hedge* left_neighbour(vertex* v) const;

		void plot(helper_map& helpers,
				  gr::Animation& animation);

	private:
		hedge* aux_left_neighbour(vertex* v,
								  Node* node,
								  hedge* candidate) const;
		unsigned aux_plot(Node* node,
						  helper_map& helpers,
						  gr::Animation& animation,
						  unsigned min);
	};


	std::vector<face*> make_monotone(DCEL& D,
									 gr::Animation& animation);
}