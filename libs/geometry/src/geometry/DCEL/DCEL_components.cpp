#include <utility>

#include "geometry/DCEL/DCEL_components.h"


namespace geometry::DCEL
{
	Vertex::Vertex(real x,
				   real y,
				   Hedge* inc_edge) :
			x(std::move(x)),
			y(std::move(y)),
			inc_edge(inc_edge)
	{}

	Hedge::Hedge(Vertex* origin,
				 Hedge* prev,
				 Hedge* next,
				 Hedge* twin,
				 Face* inc_face) :
			origin(origin),
			prev(prev),
			next(next),
			twin(twin),
			inc_face(inc_face)
	{}

	Face::Face(std::vector<Hedge*> inner_comp,
			   Hedge* outer_comp) :
			inner_comp(std::move(inner_comp)),
			outer_comp(outer_comp)
	{}
}