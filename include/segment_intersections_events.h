#pragma once

#include "segment_intersections_utils.h"
#include "graphics/view/Display_canvas.h"
#include "geometry/utils/Event_queue.h"


namespace segment_intersections_events
{
	namespace gr = graphics;
	namespace geo = geometry;
	using namespace segment_intersections_utils;

	struct event;

	struct queue_cmp
	{
		bool operator()(const event& e1,
						const event& e2) const;
	};

	typedef geo::Event_queue<event, queue_cmp> queue;

	struct event
	{
		point p;
		std::vector<unsigned> U;
		std::vector<unsigned> L;
		std::vector<unsigned> C;

		gr::Animation* animation;
		tree* T;
		queue* Q;

		event() = default;
		event(const point& p,
			  gr::Animation* animation,
			  tree* T,
			  queue* Q);

		void handle() const;
	};

	queue init_queue_and_tree(segment_set& S,
							  gr::Animation& animation);
}