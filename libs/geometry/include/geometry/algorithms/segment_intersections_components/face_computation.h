#pragma once

#include "geometry/model/DCEL.h"
#include "geometry/algorithms/segment_intersections_components/sic_tree.h"


namespace geometry::segment_intersections_components
{
	struct link
	{
		hedge* leftmost;
		hedge* helper;

		link(hedge* leftmost,
			 hedge* helper) :
				leftmost(leftmost),
				helper(helper)
		{}
	};

	void init_marks(DCEL& D,
					DCEL::mark_t interior,
					DCEL::mark_t exterior,
					DCEL::mark_t leftmost);

	void face_computation_handle_up_edge(hedge* h,
										 std::vector<link>& links,
										 tree& T,
										 DCEL::mark_t leftmost);

	void face_computation_handle_down_edge(hedge* h,
										   std::vector<link>& links,
										   tree& T,
										   DCEL::mark_t leftmost);

	std::vector<link> make_links(DCEL& D,
								 DCEL::mark_t leftmost);

	void make_one_face(DCEL& D,
					   hedge* h,
					   DCEL::mark_t treated);

	void make_one_face(DCEL& D,
					   hedge* h,
					   face* f,
					   DCEL::mark_t treated);

	void make_faces(DCEL& D,
					std::vector<link>& links,
					DCEL::mark_t interior,
					DCEL::mark_t exterior);

	void compute_faces(DCEL& D);
}