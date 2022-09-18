#include <iostream>
#include "geometry/utils/event_queue.h"


namespace geo = geometry;

class Event_queue;

struct event
{
	int a = 0;
	Event_queue* queue;

	explicit event(int a,
				   Event_queue* queue) :
			a(a),
			queue(queue)
	{}

	void handle() const;
};

class Event_queue : public geo::event_queue<event>
{
	bool compare(const event& e1,
				 const event& e2) const override
	{
		return e1.a <= e2.a;
	}

	bool are_equal(const event& e1,
				   const event& e2) const override
	{
		return e1.a == e2.a;
	}
};


void event::handle() const
{
	std::cout << a << std::endl;
	if (a == 0)
	{ return; }

	event e1(a - 1, queue);
	event e2(a - 1, queue);
	queue->push_event(e1);
	queue->push_event(e2);
}


int main()
{
	auto queue = Event_queue();

	event e0(3, &queue);
	queue.push_event(e0);
	queue.handle_events();

	return 0;
}