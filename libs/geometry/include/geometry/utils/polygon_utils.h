#pragma once

#include <vector>
#include "geometry/model/point.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	using Polygon = std::vector<point>;

	bool clockwise_orientation(const Polygon& P);
}