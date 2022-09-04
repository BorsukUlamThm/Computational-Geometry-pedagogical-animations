#pragma once

#include "Point_2.h"


namespace geometry
{
	/*!
	 * A Segment_2 is a 2D segment defined by the (x, y) coordinate of its
	 * endpoints
	 */
	template<typename Real>
	struct Segment_2
	{
		typedef Point_2<Real> Endpoint;
		Endpoint p1 {};
		Endpoint p2 {};

		Segment_2() = default;
		Segment_2(const Endpoint& p1,
				  const Endpoint& p2);
		Segment_2(const Real& p1_x,
				  const Real& p1_y,
				  const Real& p2_x,
				  const Real& p2_y);
		~Segment_2() = default;
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename Real>
	Segment_2<Real>::Segment_2(const Endpoint& p1,
							   const Endpoint& p2):
			p1(p1),
			p2(p2)
	{}

	template<typename Real>
	Segment_2<Real>::Segment_2(const Real& p1_x,
							   const Real& p1_y,
							   const Real& p2_x,
							   const Real& p2_y):
			p1(p1_x, p1_y),
			p2(p2_x, p2_y)
	{}

	template<typename Real>
	bool operator==(const Segment_2<Real>& s1,
					const Segment_2<Real> s2)
	{
		return s1.p1 == s2.p1 && s1.p2 == s2.p2;
	}
}