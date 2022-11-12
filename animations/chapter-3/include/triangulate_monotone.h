#pragma once

#include "pt_utils.h"


namespace polygon_triangulation
{
	typedef std::vector<vertex*> stack;

	void triangulate_monotone(DCEL& D,
							  face* f,
							  gr::Animation& animation);
}