#include "graphics/model/shapes/Line_shp.h"


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
		line = Line_obj(segment);
		color = col;
	}

	Line_shp::Line_shp(const Point_obj& point1,
					   const Point_obj& point2,
					   Color col)
	{
		line = Line_obj(point1, point2);
		color = col;
	}

	Line_shp::Line_shp(const Coordinate& x1,
					   const Coordinate& y1,
					   const Coordinate& x2,
					   const Coordinate& y2,
					   Color col)
	{
		line = Line_obj(x1, y1, x2, y2);
		color = col;
	}

	Coordinate Line_shp::get_a() const
	{ return line.param_a; }

	Coordinate Line_shp::get_b() const
	{ return line.param_b; }

	Coordinate Line_shp::get_c() const
	{ return line.param_c; }

	Color Line_shp::get_color() const
	{ return color; }

	void Line_shp::write(std::ostream& os) const
	{
		os << LINE_NAME << " "
		   << line << " "
		   << color;
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
		is >> line.line
		   >> line.color;
		return is;
	}
}