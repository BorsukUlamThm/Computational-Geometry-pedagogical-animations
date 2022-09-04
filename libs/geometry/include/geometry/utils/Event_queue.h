#pragma once

#include <boost/heap/priority_queue.hpp>


namespace geometry
{
	template<typename Event>
	class Event_queue
	{
		// The Event class needs to have two things
		// An overload of the operator <
		// and a method void handle() const
	private:
		boost::heap::priority_queue <Event> heap;

	public:
		Event_queue() = default;
		~Event_queue() = default;

		void push_event(const Event& event);
		void handle_events();
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Event>
	void Event_queue<Event>::push_event(const Event& event)
	{ heap.push(event); }

	template<typename Event>
	void Event_queue<Event>::handle_events()
	{
		while (!heap.empty())
		{
			heap.top().handle();
			heap.pop();
		}
	}
}