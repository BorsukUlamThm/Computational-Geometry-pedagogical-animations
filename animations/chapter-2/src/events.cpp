#include <map>
#include "../include/events.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/line_intersections.h"


namespace segment_intersections
{
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
		gr::Coordinate x(p.x);
		gr::Coordinate y(p.y);
		animation->get(EVENT).clear();
		animation->get(EVENT).add_horizontal_line(y);
		animation->get(EVENT).add_point(x, y, gr::GREEN, 8);
		animation->make_new_frame();

		if (U.size() + L.size() + C.size() > 1)
		{
			animation->get(INTERSECTIONS).add_point(x, y, gr::YELLOW);
		}

		T->set_event_p(p);
		T->set_comparison_just_above();
		for (auto& i : L)
		{ T->remove(i); }
		for (auto& i : C)
		{ T->remove(i); }

		if (L.size() + C.size() > 0)
		{ T->plot(animation); }

		T->set_comparison_just_below();
		for (auto& i : U)
		{ T->insert(i); }
		for (auto& i : C)
		{ T->insert(i); }

		if (U.size() + C.size() > 0)
		{ T->plot(animation); }

		if (U.size() + C.size() == 0)
		{
			unsigned i = T->left_neighbour(p);
			unsigned j = T->right_neighbour(p);
			find_new_event(i, j);
		}
		else
		{
			unsigned l = leftmost_segment();
			auto left_node = T->find_left_neighbour(l);
			unsigned ll = (left_node ? left_node->root : -1);
			find_new_event(ll, l);

			unsigned r = rightmost_segment();
			auto right_node = T->find_right_neighbour(r);
			unsigned rr = (right_node ? right_node->root : -1);
			find_new_event(r, rr);
		}
	}

	void event::find_new_event(unsigned i,
							   unsigned j) const
	{
		if (i == -1 || j == -1)
		{ return; }

		segment si = T->get_ith_segment(i);
		segment sj = T->get_ith_segment(j);

		gr::Coordinate xi1(si.p1.x);
		gr::Coordinate yi1(si.p1.y);
		gr::Coordinate xi2(si.p2.x);
		gr::Coordinate yi2(si.p2.y);
		gr::Coordinate xj1(sj.p1.x);
		gr::Coordinate yj1(sj.p1.y);
		gr::Coordinate xj2(sj.p2.x);
		gr::Coordinate yj2(sj.p2.y);
		animation->get(EVENT).add_segment(xi1, yi1, xi2, yi2, gr::PURPLE);
		animation->get(EVENT).add_segment(xj1, yj1, xj2, yj2, gr::PURPLE);

		if (!geo::segment_intersect(si, sj))
		{
			animation->make_new_frame();
			animation->get(EVENT).erase_last_k_shapes(2);
			return;
		}

		point inter = geo::line_intersection(si, sj);
		gr::Coordinate x(inter.x);
		gr::Coordinate y(inter.y);

		if (geo::point_below_point(inter, p))
		{
			animation->get(INTERSECTIONS).add_point(x, y, gr::YELLOW);
			if (inter != T->get_ith_segment(i).p2)
			{ Q->insert_contained_point(inter, i, animation, T); }
			if (inter != T->get_ith_segment(j).p2)
			{ Q->insert_contained_point(inter, j, animation, T); }
		}

		animation->make_new_frame();
		animation->get(EVENT).erase_last_k_shapes(2);
	}

	unsigned event::leftmost_segment() const
	{
		std::vector<unsigned> UC;
		for (unsigned i : U)
		{ UC.push_back(i); }
		for (unsigned i : C)
		{ UC.push_back(i); }

		unsigned l = UC[0];
		for (unsigned i : UC)
		{
			if (T->compare(i, l))
			{ l = i; }
		}

		return l;
	}

	unsigned event::rightmost_segment() const
	{
		std::vector<unsigned> UC;
		for (unsigned i : U)
		{ UC.push_back(i); }
		for (unsigned i : C)
		{ UC.push_back(i); }

		unsigned r = UC[0];
		for (unsigned i : UC)
		{
			if (T->compare(r, i))
			{ r = i; }
		}

		return r;
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

	void queue::insert_contained_point(const point& p,
									   unsigned i,
									   gr::Animation* animation,
									   tree* T)
	{ aux_insert_contained_point(p, i, animation, T, root); }

	bool queue::compare(const event& evt1,
						const event& evt2) const
	{
		return geo::point_below_point(evt1.p, evt2.p);
	}

	bool queue::are_equal(const event& evt1,
						  const event& evt2) const
	{
		return evt1.p == evt2.p;
	}

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

	void queue::aux_insert_contained_point(const point& p,
										   unsigned i,
										   gr::Animation* animation,
										   tree* T,
										   geo::AVL_node<event>*& node)
	{
		if (node == nullptr)
		{
			event evt(p, animation, T, this);
			evt.C.insert(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.C.insert(i);
			return;
		}

		if (geo::point_below_point(p, node->root.p))
		{
			aux_insert_contained_point(p, i, animation, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_contained_point(p, i, animation, T, node->right);
		node->update_depth();
		balance(node);
	}
}