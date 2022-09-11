#include <map>
#include "segment_intersections_events.h"
#include "geometry/utils/point_comparisons.h"


namespace segment_intersections_events
{
	bool queue_cmp::operator()(const event& evt1,
							   const event& evt2) const
	{
		return geo::point_below_point(evt1.p, evt2.p);
	}

	bool queue_cmp::are_equal(const event& evt1,
							  const event& evt2) const
	{
		return evt1.p == evt2.p;
	}

	event::event(const point& p,
				 gr::Animation* animation,
				 tree* T,
				 queue* Q) :
			p(p),
			animation(animation),
			T(T),
			Q(Q)
	{}

	void event::handle() const
	{
		auto x = boost::rational_cast<gr::Coordinate>(p.x);
		auto y = boost::rational_cast<gr::Coordinate>(p.y);
		animation->get(EVENT).add_horizontal_line(y);
		animation->get(EVENT).add_point(x, y, gr::GREEN);
		animation->make_new_frame();
		animation->get(EVENT).clear();

		std::cout << x << " " << y << std::endl << "U :";
		for (auto& i : U)
			std::cout << " " << i;
		std::cout << std::endl << "L :";
		for (auto& i : L)
			std::cout << " " << i;
		std::cout << std::endl << std::endl;

		if (U.size() + L.size() + C.size() > 1)
		{
			animation->get(INTERSECTIONS).add_point(x, y, gr::YELLOW);
		}

		T->get_order().just_above = true;
		for (auto& i : L)
		{ T->remove(i); }
		for (auto& i : C)
		{ T->remove(i); }

		T->get_order().just_above = false;
		for (auto& i : U)
		{ T->insert(i); }
		for (auto& i : C)
		{ T->insert(i); }

		if (U.size() + C.size() == 0)
		{
			//			unsigned il = T->find_left_neighbour()->root;
		}
	}

	queue::queue(segment_set& S,
				 gr::Animation& animation,
				 tree& T)
	{
		for (unsigned i = 0; i < S.size(); ++i)
		{
			insert_upper_point(S[i].p1, i, &animation, &T);
			insert_lower_point(S[i].p2, i, &animation, &T);
		}
	}

	void queue::insert_upper_point(const point& p,
								   unsigned i,
								   gr::Animation* animation,
								   tree* T)
	{ aux_insert_upper_point(p, i, animation, T, root); }

	void queue::insert_lower_point(const point& p,
								   unsigned i,
								   gr::Animation* animation,
								   tree* T)
	{ aux_insert_lower_point(p, i, animation, T, root); }

	void queue::aux_insert_upper_point(const point& p,
									   unsigned i,
									   gr::Animation* animation,
									   tree* T,
									   geo::AVL_node<event>*& node)
	{
		if (node == nullptr)
		{
			event evt(p, animation, T, this);
			evt.U.push_back(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.U.push_back(i);
			return;
		}

		if (geo::point_below_point(p, node->root.p))
		{
			aux_insert_upper_point(p, i, animation, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_upper_point(p, i, animation, T, node->right);
		node->update_depth();
		balance(node);
	}

	void queue::aux_insert_lower_point(const point& p,
									   unsigned i,
									   gr::Animation* animation,
									   tree* T,
									   geo::AVL_node<event>*& node)
	{
		if (node == nullptr)
		{
			event evt(p, animation, T, this);
			evt.L.push_back(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.L.push_back(i);
			return;
		}

		if (geo::point_below_point(p, node->root.p))
		{
			aux_insert_lower_point(p, i, animation, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_lower_point(p, i, animation, T, node->right);
		node->update_depth();
		balance(node);
	}
}