#include "geometry/algorithms/segment_intersections_components/sic_utils.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry::segment_intersections_components
{
	DCEL brute_dcel(const std::vector<segment_2>& S)
	{
		DCEL D;
		for (auto& s : S)
		{
			auto* v1 = new DCEL::vertex(s.p1.x, s.p1.y);
			auto* v2 = new DCEL::vertex(s.p2.x, s.p2.y);
			auto* h12 = new DCEL::hedge();
			auto* h21 = new DCEL::hedge();

			v1->inc_edge = h12;
			v2->inc_edge = h21;
			h12->origin = v1;
			h12->prev = h21;
			h12->next = h21;
			h12->twin = h21;
			h21->origin = v2;
			h21->prev = h12;
			h21->next = h12;
			h21->twin = h12;

			D.vertices.push_back(v1);
			D.vertices.push_back(v2);
			D.half_edges.push_back(h12);
			D.half_edges.push_back(h21);
		}

		return D;
	}

	bool up_edge(hedge* h)
	{
		point_2 v1(h->origin->x, h->origin->y);
		point_2 v2(h->twin->origin->x, h->twin->origin->y);

		return point_below_point(v1, v2);
	}

	bool hedge_below_hedge(hedge* h1, hedge* h2)
	{
		point_2 p1(h1->origin->x, h1->origin->y);
		point_2 p2(h2->origin->x, h2->origin->y);

		return point_below_point(p1, p2);
	}

	std::map<DCEL::hedge*, unsigned> make_index_map(const DCEL& D)
	{
		std::map<DCEL::hedge*, unsigned> map;

		for (unsigned i = 0; i < D.half_edges.size(); ++i)
		{
			map[D.half_edges[i]] = i;
		}

		return map;
	}
}