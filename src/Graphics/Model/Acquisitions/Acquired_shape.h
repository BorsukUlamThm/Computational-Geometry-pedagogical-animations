#pragma once

#include "Graphics/Model/Global_variables.h"


namespace graphics
{
	struct Acquired_shape
	{
		virtual ~Acquired_shape() = default;
	};

	struct Acquired_point : public Acquired_shape
	{
		Coordinate abscissa = 0;
		Coordinate ordinate = 0;

		Acquired_point(const Coordinate& x,
					   const Coordinate& y)
		{
			abscissa = x;
			ordinate = y;
		}
	};

	struct Acquired_segment : public Acquired_shape
	{
		Coordinate origin_x = 0;
		Coordinate origin_y = 0;
		Coordinate destination_x = 0;
		Coordinate destination_y = 0;

		Acquired_segment(const Coordinate& ogn_x,
						 const Coordinate& ogn_y,
						 const Coordinate& dst_x,
						 const Coordinate& dst_y)
		{
			origin_x = ogn_x;
			origin_y = ogn_y;
			destination_x = dst_x;
			destination_y = dst_y;
		}
	};
}