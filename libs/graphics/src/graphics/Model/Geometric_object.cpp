#include "graphics/Model/Geometric_object.h"


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
							 const graphics::Point_obj& dst) :
			Segment_obj(ogn.abscissa, ogn.ordinate,
						dst.abscissa, dst.ordinate)
	{}

	Circle_obj::Circle_obj(const Coordinate& x,
						   const Coordinate& y,
						   const Coordinate& rad)
	{
		center_x = x;
		center_y = y;
		radius = rad;
	}

	Line_obj::Line_obj(const Coordinate& a,
					   const Coordinate& b,
					   const Coordinate& c)
	{
		param_a = a;
		param_b = b;
		param_c = c;
	}

	Line_obj::Line_obj(const Coordinate& x1,
					   const Coordinate& y1,
					   const Coordinate& x2,
					   const Coordinate& y2)
	{
		param_a = y2 - y1;
		param_b = x1 - x2;
		param_c = -param_a * x1 - param_b * y1;
	}

	Line_obj::Line_obj(const Point_obj& point1,
					   const Point_obj& point2) :
			Line_obj(point1.abscissa, point1.ordinate,
					 point2.abscissa, point2.ordinate)
	{}

	Line_obj::Line_obj(const Segment_obj& segment) :
			Line_obj(segment.origin_x,
					 segment.origin_y,
					 segment.destination_x,
					 segment.destination_y)
	{}
}