#pragma once

#include <queue>
#include <vector>


namespace geometry
{
	template<typename Event, typename Compare>
	class Event_queue
			: public std::priority_queue<Event, std::vector<Event>, Compare>
	{
		// The Event class needs to have a method void handle() const

		typedef std::priority_queue<Event, std::vector<Event>, Compare> super;

	public:
		Event_queue() = default;
		explicit Event_queue(const Compare& compare);
		~Event_queue() = default;

		void push_event(const Event& event);
		void handle_events();
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Event, typename Compare>
	Event_queue<Event, Compare>::Event_queue(const Compare& compare) :
			super(compare)
	{}

	template<typename Event, typename Compare>
	void Event_queue<Event, Compare>::push_event(const Event& event)
	{ super::push(event); }

	template<typename Event, typename Compare>
	void Event_queue<Event, Compare>::handle_events()
	{
		while (!super::empty())
		{
			Event event = super::top();
			super::pop();
			event.handle();
		}
	}
}