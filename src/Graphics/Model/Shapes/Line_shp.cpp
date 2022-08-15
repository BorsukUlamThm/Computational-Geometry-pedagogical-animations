#include "Graphics/Model/Shapes/Line_shp.h"


namespace graphics
{
	Line_shp::Line_shp(const Coordinate& a,
					   const Coordinate& b,
					   const Coordinate& c,
					   Color col)
	{
		line = Line_obj(a, b, c);
		color = col;
	}

	Line_shp::Line_shp(const Line_shp& other) : Shape(other)
	{
		line = Line_obj(other.line);
		color = other.color;
	}

	Line_shp::Line_shp(const Segment_obj& segment,
					   Color col)
	{
		Coordinate ogn_x = segment.origin_x;
		Coordinate ogn_y = segment.origin_y;
		Coordinate dst_x = segment.destination_x;
		Coordinate dst_y = segment.destination_y;
		aux_constructor(ogn_x, ogn_y, dst_x, dst_y, col);
	}

	Line_shp::Line_shp(const Point_obj& point1,
					   const Point_obj& point2,
					   Color col)
	{
		Coordinate x1 = point1.abscissa;
		Coordinate y1 = point1.ordinate;
		Coordinate x2 = point2.abscissa;
		Coordinate y2 = point2.ordinate;
		aux_constructor(x1, y1, x2, y2, col);
	}

	Line_shp::Line_shp(const Coordinate& x1,
					   const Coordinate& y1,
					   const Coordinate& x2,
					   const Coordinate& y2,
					   Color col)
	{
		aux_constructor(x1, y1, x2, y2, col);
	}

	Coordinate Line_shp::get_a() const
	{ return line.a; }

	Coordinate Line_shp::get_b() const
	{ return line.b; }

	Coordinate Line_shp::get_c() const
	{ return line.c; }

	Color Line_shp::get_color() const
	{ return color; }

	void Line_shp::write(std::ostream& os) const
	{
		os << LINE_NAME << " "
		   << line.a << " "
		   << line.b << " "
		   << line.c << " "
		   << color;
	}

	void Line_shp::aux_constructor(const Coordinate& x1,
								   const Coordinate& y1,
								   const Coordinate& x2,
								   const Coordinate& y2,
								   Color col)
	{
		line.a = y2 - y1;
		line.b = x1 - x2;
		line.c = -line.a * x1 - line.b * y1;
		color = col;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Line_shp& line)
	{
		line.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Line_shp& line)
	{
		is >> line.line.a
		   >> line.line.b
		   >> line.line.c
		   >> line.color;
		return is;
	}
}