#pragma once

#include "tree.h"
#include "graphics/view/Animation_canvas.h"
#include "geometry/utils/event_queue.h"


namespace segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	class queue;

	struct event
	{
		point p;
		std::vector<unsigned> U;
		std::vector<unsigned> L;
		std::set<unsigned> C;

		gr::Animation* animation = nullptr;
		tree* T = nullptr;
		queue* Q = nullptr;

		event() = default;
		event(const point& p,
			  gr::Animation* animation,
			  tree* T,
			  queue* Q);

		void handle() const;

	private:
		void find_new_event(unsigned i,
							unsigned j) const;
		unsigned leftmost_segment() const;
		unsigned rightmost_segment() const;
	};

	class queue : public geo::event_queue<event>
	{
	public:
		queue(segment_set& S,
			  gr::Animation& animation,
			  tree& T);

		void insert_upper_point(unsigned i,
								gr::Animation* animation,
								tree* T);
		void insert_lower_point(unsigned i,
								gr::Animation* animation,
								tree* T);
		void insert_contained_point(const point& p,
									unsigned i,
									gr::Animation* animation,
									tree* T);

	private:
		bool compare(const event& evt1,
					 const event& evt2) const override;
		bool are_equal(const event& evt1,
					   const event& evt2) const override;

		void aux_insert_upper_point(unsigned i,
									gr::Animation* animation,
									tree* T,
									Node*& node);
		void aux_insert_lower_point(unsigned i,
									gr::Animation* animation,
									tree* T,
									Node*& node);
		void aux_insert_contained_point(const point& p,
										unsigned i,
										gr::Animation* animation,
										tree* T,
										Node*& node);
	};
}