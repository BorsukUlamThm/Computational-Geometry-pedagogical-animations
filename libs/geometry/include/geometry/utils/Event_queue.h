#pragma once

#include "AVL.h"


namespace geometry
{
	template<typename Event, typename Compare>
	class Event_queue: public AVL_tree<Event, Compare>
	{
		// The Event class needs to have a method void handle() const

		typedef AVL_tree<Event, Compare> super;

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
	{ super::insert(event); }

	template<typename Event, typename Compare>
	void Event_queue<Event, Compare>::handle_events()
	{
		while (!super::is_empty())
		{
			Event event = super::extract_max(super::root);
			event.handle();
		}
	}
}