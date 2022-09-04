#pragma once

#include "geometry/DCEL/DCEL_components.h"
#include <vector>


namespace geometry::DCEL
{
	class DCEL
	{
	private:
		std::vector<Vertex_ptr> vertices{};
		std::vector<Hedge_ptr> half_edges{};
		std::vector<Face_ptr> faces{};

	public:
		void test();
	};
}