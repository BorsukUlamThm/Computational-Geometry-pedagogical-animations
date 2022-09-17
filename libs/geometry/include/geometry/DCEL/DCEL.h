#pragma once

#include "geometry/DCEL/DCEL_components.h"
#include "geometry/model/point.h"
#include "geometry/model/segment.h"
#include <vector>
#include <iostream>


namespace geometry::DCEL
{
	class DCEL
	{
	private:
		std::vector<Vertex*> vertices {};
		std::vector<Hedge*> half_edges {};
		std::vector<Face*> faces {};

	public:
		DCEL() = default;
		explicit DCEL(const std::vector<point>& P);
		explicit DCEL(const std::vector<segment>& S);
		~DCEL();

		bool is_valid();

		friend std::ostream& operator<<(std::ostream& os,
										const DCEL& dcel);
	};

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& dcel);
}