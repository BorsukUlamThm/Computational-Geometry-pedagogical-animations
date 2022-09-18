#pragma once

#include "AVL.h"


namespace geometry
{
	template<typename Event>
	class event_queue : public AVL_tree<Event>
	{
		// The Event class needs to have a method void handle() const

		typedef AVL_tree<Event> super;
		using super::insert;
		using super::is_empty;
		using super::extract_max;

	public:
		event_queue() = default;
		~event_queue() = default;

		void push_event(const Event& event);
		void handle_events();

	protected:
		bool virtual compare(const Event& e1,
							 const Event& e2) const = 0;
		bool virtual are_equal(const Event& e1,
							   const Event& e2) const = 0;
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Event>
	void event_queue<Event>::push_event(const Event& event)
	{ super::insert(event); }

	template<typename Event>
	void event_queue<Event>::handle_events()
	{
		while (!super::is_empty())
		{
			Event event = super::extract_max(super::root);
			event.handle();
		}
	}
}