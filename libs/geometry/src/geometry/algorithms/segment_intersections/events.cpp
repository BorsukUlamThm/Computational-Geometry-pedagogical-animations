#include "geometry/algorithms/segment_intersections/events.h"
#include "geometry/utils/point_comparisons.h"
#include "geometry/utils/line_intersections.h"


namespace geometry::segment_intersections_components
{
	event::event(const point_2& p,
				 DCEL* D,
				 tree* T,
				 queue* Q) :
			p(p),
			D(D),
			T(T),
			Q(Q)
	{}

	void event::handle() const
	{
		T->plot_point(p);

		T->set_event_p(p);
		make_intersection();

		T->plot();

		T->set_comparison_just_above();
		for (auto& i : L)
		{ T->remove(i); }
		for (auto& i : C)
		{ T->remove(i); }

		T->plot();

		T->set_comparison_just_below();
		for (auto& i : U)
		{ T->insert(i); }
		for (auto& i : C)
		{ T->insert(i); }

		T->plot();

		if (U.size() + C.size() == 0)
		{
			hedge* i = T->left_neighbour(p);
			hedge* j = T->right_neighbour(p);
			find_new_event(i, j);
		}
		else
		{
			hedge* l = leftmost_segment();
			auto left_node = T->find_left_neighbour(l);
			hedge* ll = (left_node ? left_node->root : nullptr);
			find_new_event(ll, l);

			hedge* r = rightmost_segment();
			auto right_node = T->find_right_neighbour(r);
			hedge* rr = (right_node ? right_node->root : nullptr);
			find_new_event(r, rr);
		}
	}

	void event::make_intersection() const
	{
		if (U.size() + L.size() + C.size() < 2)
		{ return; }

		auto* v = new DCEL::vertex(p.x, p.y);
		D->vertices.push_back(v);

		std::vector<hedge*> IA;
		for (auto& h : L)
		{ IA.push_back(h); }
		std::vector<hedge*> IB;
		for (auto& h : U)
		{ IB.push_back(h); }

		for (auto& h : C)
		{
			auto* d = new DCEL::hedge();
			auto* u = new DCEL::hedge();
			D->half_edges.push_back(d);
			D->half_edges.push_back(u);
			IA.push_back(d);
			IB.push_back(h);

			h->prev->next = d;
			h->twin->next->prev = u;

			d->origin = h->origin;
			d->origin->inc_edge = d;
			d->prev = (h->prev == h->twin ? u : h->prev);
			d->twin = u;

			u->origin = v;
			v->inc_edge = u;
			u->next = (h->twin->next == h ? d : h->twin->next);
			u->twin = d;

			h->origin = v;
		}

		T->set_comparison_just_above();
		std::sort(IA.begin(), IA.end(),
				  [this](hedge* h1, hedge* h2)
				  { return T->compare(h1, h2); });
		T->set_comparison_just_below();
		std::sort(IB.begin(), IB.end(),
				  [this](hedge* h1, hedge* h2)
				  { return T->compare(h1, h2); });

		unsigned na = IA.size();
		unsigned nb = IB.size();
		for (unsigned i = 0; i < na - 1; ++i)
		{
			IA[i]->next = IA[i + 1]->twin;
			IA[i + 1]->twin->prev = IA[i];
		}
		for (unsigned i = 0; i < nb - 1; ++i)
		{
			IB[i + 1]->twin->next = IB[i];
			IB[i]->prev = IB[i + 1]->twin;
		}
		IA[0]->twin->prev = IB[0]->twin;
		IB[0]->twin->next = IA[0]->twin;
		IA[na - 1]->next = IB[nb - 1];
		IB[nb - 1]->prev = IA[na - 1];

		v->inc_edge = IB[0];
		for (auto& h : L)
		{
			D->delete_vertex(h->twin->origin);
			h->twin->origin = v;
		}
		for (auto& h : U)
		{
			D->delete_vertex(h->origin);
			h->origin = v;
		}
	}

	void event::find_new_event(hedge* i,
							   hedge* j) const
	{
		if (i == nullptr || j == nullptr)
		{ return; }

		gr::Coordinate ix1(i->origin->x);
		gr::Coordinate iy1(i->origin->y);
		gr::Coordinate ix2(i->twin->origin->x);
		gr::Coordinate iy2(i->twin->origin->y);
		gr::Coordinate jx1(j->origin->x);
		gr::Coordinate jy1(j->origin->y);
		gr::Coordinate jx2(j->twin->origin->x);
		gr::Coordinate jy2(j->twin->origin->y);
		T->animation[3].add_segment(ix1, iy1, ix2, iy2, gr::PURPLE);
		T->animation[3].add_segment(jx1, jy1, jx2, jy2, gr::PURPLE);
		T->animation.make_new_frame();
		T->animation[3].clear();

		if (!hedges_intersect(i, j))
		{ return; }

		point_2 inter = line_intersection(i, j);

		gr::Coordinate x(inter.x);
		gr::Coordinate y(inter.y);
		T->animation[0].add_point(x, y, gr::YELLOW);
		T->animation.make_new_frame();

		if (point_below_point(inter, p))
		{
			point_2 low_i(i->twin->origin->x, i->twin->origin->y);
			point_2 low_j(j->twin->origin->x, j->twin->origin->y);

			if (inter != low_i)
			{ Q->insert_contained_point(inter, i, D, T); }
			if (inter != low_j)
			{ Q->insert_contained_point(inter, j, D, T); }
		}
	}

	hedge* event::leftmost_segment() const
	{
		std::vector<hedge*> UC;
		for (hedge* i : U)
		{ UC.push_back(i); }
		for (hedge* i : C)
		{ UC.push_back(i); }

		hedge* l = UC[0];
		for (hedge* i : UC)
		{
			if (T->compare(i, l))
			{ l = i; }
		}

		return l;
	}

	hedge* event::rightmost_segment() const
	{
		std::vector<hedge*> UC;
		for (hedge* i : U)
		{ UC.push_back(i); }
		for (hedge* i : C)
		{ UC.push_back(i); }

		hedge* r = UC[0];
		for (hedge* i : UC)
		{
			if (T->compare(r, i))
			{ r = i; }
		}

		return r;
	}

	queue::queue(DCEL& D,
				 tree& T)
	{
		for (auto& h : D.half_edges)
		{
			if (up_edge(h))
			{ continue; }
			insert_upper_point(h, &D, &T);
			insert_lower_point(h, &D, &T);
		}
	}

	void queue::insert_upper_point(hedge* i,
								   DCEL* D,
								   tree* T)
	{ aux_insert_upper_point(i, D, T, root); }

	void queue::insert_lower_point(hedge* i,
								   DCEL* D,
								   tree* T)
	{ aux_insert_lower_point(i, D, T, root); }

	void queue::insert_contained_point(const point_2& p,
									   hedge* i,
									   DCEL* D,
									   tree* T)
	{ aux_insert_contained_point(p, i, D, T, root); }

	bool queue::compare(const event& evt1,
						const event& evt2) const
	{
		return point_below_point(evt1.p, evt2.p);
	}

	bool queue::are_equal(const event& evt1,
						  const event& evt2) const
	{
		return evt1.p == evt2.p;
	}

	void queue::aux_insert_upper_point(hedge* i,
									   DCEL* D,
									   tree* T,
									   AVL_node<event>*& node)
	{
		point_2 p(i->origin->x, i->origin->y);

		if (node == nullptr)
		{
			event evt(p, D, T, this);
			evt.U.push_back(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.U.push_back(i);
			return;
		}

		if (point_below_point(p, node->root.p))
		{
			aux_insert_upper_point(i, D, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_upper_point(i, D, T, node->right);
		node->update_depth();
		balance(node);
	}

	void queue::aux_insert_lower_point(hedge* i,
									   DCEL* D,
									   tree* T,
									   AVL_node<event>*& node)
	{
		point_2 p(i->twin->origin->x, i->twin->origin->y);

		if (node == nullptr)
		{
			event evt(p, D, T, this);
			evt.L.push_back(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.L.push_back(i);
			return;
		}

		if (point_below_point(p, node->root.p))
		{
			aux_insert_lower_point(i, D, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_lower_point(i, D, T, node->right);
		node->update_depth();
		balance(node);
	}

	void queue::aux_insert_contained_point(const point_2& p,
										   hedge* i,
										   DCEL* D,
										   tree* T,
										   AVL_node<event>*& node)
	{
		if (node == nullptr)
		{
			event evt(p, D, T, this);
			evt.C.insert(i);
			node = new Node(evt);
			return;
		}

		if (p == node->root.p)
		{
			node->root.C.insert(i);
			return;
		}

		if (point_below_point(p, node->root.p))
		{
			aux_insert_contained_point(p, i, D, T, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert_contained_point(p, i, D, T, node->right);
		node->update_depth();
		balance(node);
	}
}