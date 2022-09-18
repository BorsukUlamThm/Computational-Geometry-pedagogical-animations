#include "geometry/DCEL/DCEL_components.h"


namespace geometry
{
	DCEL::Vertex::Vertex(const real& x,
						 const real& y,
						 Hedge* inc_edge) :
			x(x),
			y(y),
			inc_edge(inc_edge)
	{}

	DCEL::Hedge::Hedge(Vertex* origin,
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

	DCEL::Face::Face(std::vector<Hedge*> inner_comp,
					 Hedge* outer_comp) :
			inner_comp(std::move(inner_comp)),
			outer_comp(outer_comp)
	{}
}