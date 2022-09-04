#pragma once

#include <boost/heap/priority_queue.hpp>


namespace geometry
{
	template<typename Event>
	class Event_queue : public boost::heap::priority_queue<Event>
	{
		// The Event class needs to have two things
		// An overload of the operator <
		// and a method void handle() const
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
	{ push(event); }

	template<typename Event>
	void Event_queue<Event>::handle_events()
	{
		while (!boost::heap::priority_queue<Event>::empty())
		{
			boost::heap::priority_queue<Event>::top().handle();
			boost::heap::priority_queue<Event>::pop();
		}
	}
}