#pragma once

#include "sic_tree.h"
#include "geometry/utils/event_queue.h"


namespace geometry::segment_intersections_components
{
	class queue;

	struct event
	{
		point_2 p;
		std::vector<hedge*> U;
		std::vector<hedge*> L;
		std::set<hedge*> C;

		DCEL* D = nullptr;
		tree* T = nullptr;
		queue* Q = nullptr;

		event() = default;
		event(const point_2& p,
			  DCEL* D,
			  tree* T,
			  queue* Q);

		void handle() const;

	private:
		void make_intersection() const;

		void find_new_event(hedge* i,
							hedge* j) const;
		hedge* leftmost_segment() const;
		hedge* rightmost_segment() const;
	};

	class queue : public event_queue<event>
	{
	public:
		queue(DCEL& D,
			  tree& T);

		void insert_upper_point(hedge* i,
								DCEL* D,
								tree* T);
		void insert_lower_point(hedge* i,
								DCEL* D,
								tree* T);
		void insert_contained_point(const point_2& p,
									hedge* i,
									DCEL* D,
									tree* T);

	private:
		bool compare(const event& evt1,
					 const event& evt2) const override;
		bool are_equal(const event& evt1,
					   const event& evt2) const override;

		void aux_insert_upper_point(hedge* i,
									DCEL* D,
									tree* T,
									Node*& node);
		void aux_insert_lower_point(hedge* i,
									DCEL* D,
									tree* T,
									Node*& node);
		void aux_insert_contained_point(const point_2& p,
										hedge* i,
										DCEL* D,
										tree* T,
										Node*& node);
	};
}