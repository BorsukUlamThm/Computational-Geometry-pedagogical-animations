#pragma once

#include <boost/rational.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "graphics/view/Display_canvas.h"
#include "geometry/model/Point_2.h"
#include "geometry/model/Segment_2.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/AVL.h"


namespace chap2_segment_intersections
{
	namespace gr = graphics;
	namespace geo = geometry;

	typedef boost::rational<boost::multiprecision::cpp_int> rational;
	typedef geo::Point_2<rational> point;
	typedef geo::Segment_2<rational> segment;

	enum Figures
	{
		SEGMENTS,
		LINE,
		NB_FIGURES
	};
	extern gr::Animation animation;

	struct Event
	{
		point p;
		std::vector<unsigned> U;
		std::vector<unsigned> L;
		std::vector<unsigned> C;

		Event() = default;

		Event(const point& p);

		void handle() const;
	};

	Event::Event(const point& p):
			p(p)
	{}

	void Event::handle() const
	{
		auto x = boost::rational_cast<float>(p.x);
		auto y = boost::rational_cast<float>(p.y);
		animation[SEGMENTS].add_point(x, y, gr::RED, 5);

		animation[LINE].clear();
		animation[LINE].add_horizontal_line(y);

		animation.make_new_frame();
		animation[SEGMENTS].erase_last_shape();
	}

	Event make_upper_event(const point& p, unsigned i)
	{
		Event event (p);
		event.U.push_back(i);

		return event;
	}

	Event make_lower_event(const point& p, unsigned i)
	{
		Event event (p);
		event.L.push_back(i);

		return event;
	}


	struct Event_order
	{
		Event_order() = default;

		bool greater_than(const Event& event1, const Event& event2)
		{
			return geo::point_above_point(event1.p, event2.p);
		}
		bool greater_than(const Event& event1, const point& p)
		{
			return geo::point_above_point(event1.p, p);
		}

		bool are_equal(const Event& event1, const Event& event2)
		{
			return event1.p == event2.p;
		}
		bool are_equal(const Event& event1, const point& p)
		{
			return event1.p == p;
		}
	};


	class Event_queue : public geo::AVL_tree<Event, Event_order>
	{
	public:
		Event_queue() = default;

		void insert_upper_point(const point& p, unsigned i);
		void insert_lower_point(const point& p, unsigned i);

		void handle_events();

	protected:
		void aux_insert_upper_point(const point& p, unsigned i, Node*& node);
		void aux_insert_lower_point(const point& p, unsigned i, Node*& node);
	};

	void Event_queue::aux_insert_upper_point(const point& p, unsigned int i, Node*& node)
	{
		if(node == nullptr)
		{
			node = new Node(make_upper_event(p, i));
			return;
		}

		if(comp.are_equal(node->root, p))
		{
			node->root.U.push_back(i);
			return;
		}

		if(comp.greater_than(node->root, p))
		{
			aux_insert_upper_point(p, i, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_upper_point(p, i, node->right);
		node->update_depth();
		balance(node);
	}

	void Event_queue::insert_upper_point(const point& p, unsigned int i)
	{
		aux_insert_upper_point(p, i, root);
	}

	void Event_queue::aux_insert_lower_point(const point& p, unsigned int i, Node*& node)
	{
		if(node == nullptr)
		{
			node = new Node(make_lower_event(p, i));
			return;
		}

		if(comp.are_equal(node->root, p))
		{
			node->root.L.push_back(i);
			return;
		}

		if(comp.greater_than(node->root, p))
		{
			aux_insert_lower_point(p, i, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_lower_point(p, i, node->right);
		node->update_depth();
		balance(node);
	}

	void Event_queue::insert_lower_point(const point& p, unsigned int i)
	{
		aux_insert_lower_point(p, i, root);
	}

	void Event_queue::handle_events()
	{
		while(!is_empty())
		{
			Event event = extract_max(root);
			event.handle();
		}
	}


}