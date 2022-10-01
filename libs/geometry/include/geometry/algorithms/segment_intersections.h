#pragma once

#include <set>
#include "geometry/model/segment_2.h"
#include "geometry/model/DCEL.h"
#include "geometry/utils/AVL.h"


namespace geometry
{
	DCEL segment_intersections(const std::vector<segment_2>& S);
}