#pragma once

#include "geometry/model/point_2.h"
#include "geometry/model/segment_2.h"
#include <vector>
#include <iostream>


namespace geometry
{
	class DCEL
	{
		struct Vertex;
		struct Hedge;
		struct Face;

	private:
		std::vector<Vertex*> vertices {};
		std::vector<Hedge*> half_edges {};
		std::vector<Face*> faces {};

	public:
		DCEL() = default;
		explicit DCEL(const std::vector<point_2>& P);
		~DCEL();

		bool is_valid();
		void clear();

		friend std::ostream& operator<<(std::ostream& os,
										const DCEL& dcel);
	};

	std::ostream& operator<<(std::ostream& os,
							 const DCEL& dcel);
}