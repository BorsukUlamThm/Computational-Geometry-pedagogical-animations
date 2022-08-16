#include "graphics/Model/Geometric_object.h"


namespace graphics
{
	Point_obj::Point_obj(const graphics::Coordinate& x,
						 const graphics::Coordinate& y)
	{
		abscissa = x;
		ordinate = y;
	}

	Segment_obj::Segment_obj(const graphics::Point_obj& ogn,
							 const graphics::Point_obj& dst)
	{
		origin = ogn;
		destination = dst;
	}

	Segment_obj::Segment_obj(const graphics::Coordinate& ogn_x,
							 const graphics::Coordinate& ogn_y,
							 const graphics::Coordinate& dst_x,
							 const graphics::Coordinate& dst_y) :
			Segment_obj(Point_obj(ogn_x, ogn_y),
						Point_obj(dst_x, dst_y))
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
			Line_obj(segment.origin.abscissa,
					 segment.origin.ordinate,
					 segment.destination.abscissa,
					 segment.destination.ordinate)
	{}

	std::ostream& operator<<(std::ostream& os,
							 const Point_obj& point)
	{
		os << point.abscissa << " "
		   << point.ordinate;

		return os;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Segment_obj& segment)
	{
		os << segment.origin << " "
		   << segment.destination;

		return os;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Circle_obj& circle)
	{
		os << circle.center_x << " "
		   << circle.center_y << " "
		   << circle.radius;

		return os;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Line_obj& line)
	{
		os << line.param_a << " "
		   << line.param_b << " "
		   << line.param_c;

		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Point_obj& point)
	{
		is >> point.abscissa
		   >> point.ordinate;

		return is;
	}

	std::istream& operator>>(std::istream& is,
							 Segment_obj& segment)
	{
		is >> segment.origin
		   >> segment.destination;

		return is;
	}

	std::istream& operator>>(std::istream& is,
							 Circle_obj& circle)
	{
		is >> circle.center_x
		   >> circle.center_y
		   >> circle.radius;

		return is;
	}

	std::istream& operator>>(std::istream& is,
							 Line_obj& line)
	{
		is >> line.param_a
		   >> line.param_b
		   >> line.param_c;

		return is;
	}
}