#include "Graphics/Model/Geometric_object.h"


namespace graphics
{
	Point_obj::Point_obj(const graphics::Coordinate& x,
						 const graphics::Coordinate& y)
	{
		abscissa = x;
		ordinate = y;
	}

	Segment_obj::Segment_obj(const graphics::Coordinate& ogn_x,
							 const graphics::Coordinate& ogn_y,
							 const graphics::Coordinate& dst_x,
							 const graphics::Coordinate& dst_y)
	{
		origin_x = ogn_x;
		origin_y = ogn_y;
		destination_x = dst_x;
		destination_y = dst_y;
	}

	Segment_obj::Segment_obj(const graphics::Point_obj& ogn,
							 const graphics::Point_obj& dst)
	{
		origin_x = ogn.abscissa;
		origin_y = ogn.ordinate;
		destination_x = ogn.abscissa;
		destination_y = ogn.ordinate;
	}

	Circle_obj::Circle_obj(const Coordinate& x, const Coordinate& y,
						   const Coordinate& rad)
	{
		center_x = x;
		center_y = y;
		radius = rad;
	}

	Line_obj::Line_obj(const Coordinate& a, const Coordinate& b,
					   const Coordinate& c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
}