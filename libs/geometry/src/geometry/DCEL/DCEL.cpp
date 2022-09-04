#include "geometry/DCEL/DCEL.h"
#include "geometry/utils/polygon_utils.h"
#include <iostream>
#include <map>


namespace geometry::DCEL
{
	DCEL::DCEL(const std::vector<Point_2<rational>>& P)
	{
		unsigned n = P.size();

		for (auto& p : P)
		{
			auto* v = new Vertex(p.x, p.y);
			auto* h1 = new Hedge();
			auto* h2 = new Hedge();

			vertices.push_back(v);
			half_edges.push_back(h1);
			half_edges.push_back(h2);
		}

		for (unsigned i = 0; i < n; ++i)
		{
			vertices[i]->inc_edge = half_edges[i];
			half_edges[i]->origin = vertices[i];

			half_edges[i]->prev = half_edges[(n + i - 1) % n];
			half_edges[i]->next = half_edges[(i + 1) % n];
			half_edges[n + i]->prev = half_edges[n + (i + 1) % n];
			half_edges[n + i]->next = half_edges[n + (n + i - 1) % n];

			half_edges[i]->twin = half_edges[n + i];
			half_edges[n + i]->twin = half_edges[i];
		}

		for (unsigned i = 0; i < n; ++i)
		{
			half_edges[n + i]->origin = half_edges[i]->next->origin;
		}

		auto* bounded = new Face();
		auto* unbounded = new Face();

		if (clockwise_orientation(P))
		{
			bounded->outer_comp = half_edges[n];
			unbounded->inner_comp = half_edges[0];
			for (unsigned i = 0; i < n; ++i)
			{
				half_edges[i]->inc_face = unbounded;
				half_edges[n + i]->inc_face = bounded;
			}
		}
		else
		{
			bounded->outer_comp = half_edges[0];
			unbounded->inner_comp = half_edges[n];
			for (unsigned i = 0; i < n; ++i)
			{
				half_edges[i]->inc_face = bounded;
				half_edges[n + i]->inc_face = unbounded;
			}
		}

		faces.push_back(bounded);
		faces.push_back(unbounded);
	}

	DCEL::~DCEL()
	{
		for (auto& ptr : vertices)
		{ delete ptr; }

		for (auto& ptr : half_edges)
		{ delete ptr; }

		for (auto& ptr : faces)
		{ delete ptr; }
	}

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& dcel)
	{
		std::map<void*, int> indexes;
		indexes[nullptr] = -1;

		for (int i = 0; i < dcel.vertices.size(); ++i)
		{ indexes[dcel.vertices[i]] = i; }

		for (int i = 0; i < dcel.half_edges.size(); ++i)
		{ indexes[dcel.half_edges[i]] = i; }

		for (int i = 0; i < dcel.faces.size(); ++i)
		{ indexes[dcel.faces[i]] = i; }

		for (int i = 0; i < dcel.vertices.size(); ++i)
		{
			os << "v" << i << " : "
			   << dcel.vertices[i]->x << " "
			   << dcel.vertices[i]->y << " "
			   << indexes[dcel.vertices[i]->inc_edge] << std::endl;
		}

		os << std::endl;

		for (int i = 0; i < dcel.half_edges.size(); ++i)
		{
			os << "h" << i << " : "
			   << indexes[dcel.half_edges[i]->origin] << " "
			   << indexes[dcel.half_edges[i]->prev] << " "
			   << indexes[dcel.half_edges[i]->next] << " "
			   << indexes[dcel.half_edges[i]->twin] << " "
			   << indexes[dcel.half_edges[i]->inc_face] << std::endl;
		}

		os << std::endl;

		for (int i = 0; i < dcel.faces.size(); ++i)
		{
			os << "f" << i << " : "
			   << indexes[dcel.faces[i]->inner_comp] << " "
			   << indexes[dcel.faces[i]->outer_comp] << std::endl;
		}

		return os;
	}
}