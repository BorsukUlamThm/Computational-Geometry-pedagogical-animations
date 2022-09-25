#pragma once

#include <vector>
#include "geometry/model/point_2.h"
#include "geometry/model/DCEL.h"
#include "geometry/utils/point_comparisons.h"


namespace geometry
{
	using polygon = std::vector<point_2>;

	bool clockwise_orientation(const polygon& P);

	DCEL DCEL_from_polygon(const polygon& P);
}