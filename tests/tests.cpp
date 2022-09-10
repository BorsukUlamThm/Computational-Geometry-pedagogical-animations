#include "graphics/view/Display_canvas.h"
#include "graphics/view/Acquisition_canvas.h"
#include "utils/Program_options.h"
#include "geometry/DCEL/DCEL.h"
#include "geometry/model/serialization.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/utils/Event_queue.h"


namespace gr = graphics;
namespace geo = geometry;

struct Event;

struct Comp
{
	bool reverse = false;

	bool operator()(const Event& e1, const Event& e2) const;
};

typedef geo::Event_queue<Event, Comp> Event_queue;

struct Event
{
	int a = 0;
	Event_queue* queue;

	explicit Event(int a, Event_queue* queue) : a(a), queue(queue) {}

	void handle() const
	{
		std::cout << a << std::endl;
		if (a == 0)
		{ return; }

		Event e1 (a - 1, queue);
		Event e2 (a - 1, queue);
		queue->push_event(e1);
		queue->push_event(e2);
	}
};

bool Comp::operator()(const Event& e1, const Event& e2) const
{
	int epsilon = reverse ? -1 : 1;
	return epsilon * e1.a < epsilon * e2.a;
}

int main(int argc, char** argv)
{
	Comp comp;
//	comp.reverse = true;
	auto* queue = new Event_queue (comp);

	Event e1 (1, queue);
	Event e2 (2, queue);
	Event e3 (3, queue);

	queue->push_event(e1);
	queue->push_event(e2);
	queue->push_event(e3);
	queue->handle_events();

	delete queue;

	return 0;
}