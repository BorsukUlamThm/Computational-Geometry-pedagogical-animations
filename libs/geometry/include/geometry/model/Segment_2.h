#pragma once

#include "Point_2.h"


namespace geometry
{
	/*!
	 * A Segment_2 is a 2D segment defined by the (x, y) coordinate of its
	 * endpoints
	 */
	template<typename real>
	struct Segment_2
	{
		typedef Point_2<real> Endpoint;
		Endpoint p1 {};
		Endpoint p2 {};

		Segment_2() = default;
		Segment_2(const Endpoint& p1,
				  const Endpoint& p2);
		Segment_2(const real& p1_x,
				  const real& p1_y,
				  const real& p2_x,
				  const real& p2_y);
		~Segment_2() = default;
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename real>
	Segment_2<real>::Segment_2(const Endpoint& p1,
							   const Endpoint& p2):
			p1(p1),
			p2(p2)
	{}

	template<typename real>
	Segment_2<real>::Segment_2(const real& p1_x,
							   const real& p1_y,
							   const real& p2_x,
							   const real& p2_y):
			p1(p1_x, p1_y),
			p2(p2_x, p2_y)
	{}

	template<typename real>
	bool operator==(const Segment_2<real>& s1,
					const Segment_2<real> s2)
	{
		return s1.p1 == s2.p1 && s1.p2 == s2.p2;
	}
}