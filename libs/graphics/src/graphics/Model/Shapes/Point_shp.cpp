#include "graphics/Model/Shapes/Point_shp.h"


namespace graphics
{
	Point_shp::Point_shp()
	{
		bounding_box = Bounding_box(point);
	}

	Point_shp::Point_shp(const Coordinate& x,
						 const Coordinate& y,
						 Color col,
						 float rad)
	{
		point = Point_obj(x, y);
		color = col;
		radius = rad;
		bounding_box = Bounding_box(point);
	}

	Point_shp::Point_shp(const Point_shp& other) : Shape(other)
	{
		point = Point_obj(other.point);
		color = other.color;
		radius = other.radius;
	}

	Coordinate Point_shp::get_abscissa() const
	{ return point.abscissa; }

	Coordinate Point_shp::get_ordinate() const
	{ return point.ordinate; }

	Color Point_shp::get_color() const
	{ return color; }

	float Point_shp::get_radius() const
	{ return radius; }

	void Point_shp::write(std::ostream& os) const
	{
		os << POINT_NAME << " "
		   << point << " "
		   << color << " "
		   << radius;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Point_shp& point)
	{
		point.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Point_shp& point)
	{
		is >> point.point
		   >> point.color
		   >> point.radius;
		return is;
	}
}