#pragma once

#include "geometry/DCEL/DCEL_components.h"
#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
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
		explicit DCEL(const std::vector<point_2>& P);
		explicit DCEL(const std::vector<segment_2>& S);
		~DCEL();

		bool is_valid();

		friend std::ostream& operator<<(std::ostream& os,
										const DCEL& dcel);
	};

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& dcel);
}