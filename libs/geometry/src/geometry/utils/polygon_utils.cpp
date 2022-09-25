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
		DCEL dcel;

		for (auto& p : P)
		{
			auto* v = new DCEL::Vertex(p.x, p.y);
			auto* h1 = new DCEL::Hedge();
			auto* h2 = new DCEL::Hedge();

			dcel.vertices.push_back(v);
			dcel.half_edges.push_back(h1);
			dcel.half_edges.push_back(h2);
		}

		for (unsigned i = 0; i < n; ++i)
		{
			dcel.vertices[i]->inc_edge = dcel.half_edges[i];
			dcel.half_edges[i]->origin = dcel.vertices[i];

			dcel.half_edges[i]->prev = dcel.half_edges[(n + i - 1) % n];
			dcel.half_edges[i]->next = dcel.half_edges[(i + 1) % n];
			dcel.half_edges[n + i]->prev = dcel.half_edges[n + (i + 1) % n];
			dcel.half_edges[n + i]->next = dcel.half_edges[n + (n + i - 1) % n];

			dcel.half_edges[i]->twin = dcel.half_edges[n + i];
			dcel.half_edges[n + i]->twin = dcel.half_edges[i];
		}

		for (unsigned i = 0; i < n; ++i)
		{
			dcel.half_edges[n + i]->origin = dcel.half_edges[i]->next->origin;
		}

		auto* bounded = new DCEL::Face();
		auto* unbounded = new DCEL::Face();

		if (clockwise_orientation(P))
		{
			bounded->outer_comp = dcel.half_edges[n];
			unbounded->inner_comp.push_back(dcel.half_edges[0]);
			for (unsigned i = 0; i < n; ++i)
			{
				dcel.half_edges[i]->inc_face = unbounded;
				dcel.half_edges[n + i]->inc_face = bounded;
			}
		}
		else
		{
			bounded->outer_comp = dcel.half_edges[0];
			unbounded->inner_comp.push_back(dcel.half_edges[n]);
			for (unsigned i = 0; i < n; ++i)
			{
				dcel.half_edges[i]->inc_face = bounded;
				dcel.half_edges[n + i]->inc_face = unbounded;
			}
		}

		dcel.faces.push_back(bounded);
		dcel.faces.push_back(unbounded);

		return dcel;
	}
}