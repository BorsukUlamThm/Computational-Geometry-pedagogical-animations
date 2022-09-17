#include "geometry/DCEL/DCEL.h"
#include "geometry/utils/polygon_utils.h"
#include "geometry/model/serialization.h"
#include <iostream>
#include <map>


namespace geometry::DCEL
{
	DCEL::DCEL(const std::vector<point_2>& P)
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
			unbounded->inner_comp.push_back(half_edges[0]);
			for (unsigned i = 0; i < n; ++i)
			{
				half_edges[i]->inc_face = unbounded;
				half_edges[n + i]->inc_face = bounded;
			}
		}
		else
		{
			bounded->outer_comp = half_edges[0];
			unbounded->inner_comp.push_back(half_edges[n]);
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

	bool DCEL::is_valid()
	{
		bool valid = true;

		for (unsigned i = 0; i < vertices.size(); ++i)
		{
			Hedge* h = vertices[i]->inc_edge;
			do
			{
				if (h->origin != vertices[i])
				{
					std::cerr << "Invalid DCEL " << i << "-th vertex incident"
							  << " edges are note all invalid" << std::endl;
					valid = false;
				}
				h = h->prev->twin;
			}
			while (h != vertices[i]->inc_edge);
		}

		for (unsigned i = 0; i < half_edges.size(); ++i)
		{
			if (half_edges[i]->prev->next != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge prev is"
						  << " invalid" << std::endl;
				valid = false;
			}
			if (half_edges[i]->next->prev != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge next is"
						  << " invalid" << std::endl;
				valid = false;
			}
			if (half_edges[i]->twin->twin != half_edges[i])
			{
				std::cerr << "Invalid DCEL " << i << "-th half edge twin is"
						  << " invalid" << std::endl;
				valid = false;
			}
		}

		for (unsigned i = 0; i < faces.size(); ++i)
		{
			if (faces[i]->outer_comp)
			{
				Hedge* h = faces[i]->outer_comp;
				do
				{
					if (h->inc_face != faces[i])
					{
						std::cerr << "Invalid DCEL " << i << "-th face"
								  << " outer_comp boundary is invalid"
								  << std::endl;
						valid = false;
					}
					h = h->next;
				}
				while (h != faces[i]->outer_comp);
			}
			for (Hedge* it : faces[i]->inner_comp)
			{
				Hedge* h = it;
				do
				{
					if (h->inc_face != faces[i])
					{
						std::cerr << "Invalid DCEL " << i << "-th face"
								  << " inner_comp boundary is invalid"
								  << std::endl;
						valid = false;
					}
					h = h->next;
				}
				while (h != it);
			}
		}

		return valid;
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
			os << "f" << i << " : [";
			auto vec = dcel.faces[i]->inner_comp;
			for (unsigned j = 0; j < vec.size(); ++j)
			{
				os << indexes[vec[j]] << (j == vec.size() - 1 ? "" : " ");
			}
			os << "] " << indexes[dcel.faces[i]->outer_comp] << std::endl;
		}

		return os;
	}
}