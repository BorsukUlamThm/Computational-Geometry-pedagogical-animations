#include "geometry/utils/polygon_utils.h"


namespace geometry
{
	bool clockwise_orientation(const polygon& P)
	{
		unsigned n = P.size();
		unsigned i_max = 0;
		for (unsigned i = 0; i < n; ++i)
		{
			if (point_above_point(P[i], P[i_max]))
			{
				i_max = i;
			}
		}

		return point_right_line(P[(i_max + 1) % n],
								P[(n + i_max - 1) % n],
								P[i_max]);
	}

	DCEL DCEL_from_polygon(const polygon& P)
	{
		unsigned n = P.size();
		DCEL D;

		for (auto& p : P)
		{
			auto* v = new DCEL::vertex(p.x, p.y);
			auto* h1 = new DCEL::hedge();
			auto* h2 = new DCEL::hedge();

			D.vertices.push_back(v);
			D.half_edges.push_back(h1);
			D.half_edges.push_back(h2);
		}

		for (unsigned i = 0; i < n; ++i)
		{
			D.vertices[i]->inc_edge = D.half_edges[i];
			D.half_edges[i]->origin = D.vertices[i];

			D.half_edges[i]->prev = D.half_edges[(n + i - 1) % n];
			D.half_edges[i]->next = D.half_edges[(i + 1) % n];
			D.half_edges[n + i]->prev = D.half_edges[n + (i + 1) % n];
			D.half_edges[n + i]->next = D.half_edges[n + (n + i - 1) % n];

			D.half_edges[i]->twin = D.half_edges[n + i];
			D.half_edges[n + i]->twin = D.half_edges[i];
		}

		for (unsigned i = 0; i < n; ++i)
		{
			D.half_edges[n + i]->origin = D.half_edges[i]->next->origin;
		}

		auto* bounded = new DCEL::face();
		auto* unbounded = new DCEL::face();

		if (clockwise_orientation(P))
		{
			bounded->outer_comp = D.half_edges[n];
			unbounded->inner_comp.push_back(D.half_edges[0]);
			for (unsigned i = 0; i < n; ++i)
			{
				D.half_edges[i]->inc_face = unbounded;
				D.half_edges[n + i]->inc_face = bounded;
			}
		}
		else
		{
			bounded->outer_comp = D.half_edges[0];
			unbounded->inner_comp.push_back(D.half_edges[n]);
			for (unsigned i = 0; i < n; ++i)
			{
				D.half_edges[i]->inc_face = bounded;
				D.half_edges[n + i]->inc_face = unbounded;
			}
		}

		D.faces.push_back(bounded);
		D.faces.push_back(unbounded);

		return D;
	}
}