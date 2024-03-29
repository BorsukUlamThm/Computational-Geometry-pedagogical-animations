#include "graphics/model/shapes/Circle_shp.h"


namespace graphics
{
	Circle_shp::Circle_shp()
	{
		bounding_box = Bounding_box(circle);
	}

	Circle_shp::Circle_shp(const Coordinate& x,
						   const Coordinate& y,
						   const Coordinate& rad,
						   Color col)
	{
		circle = Circle_obj(x, y, rad);
		color = col;
		bounding_box = Bounding_box(circle);
	}

	Circle_shp::Circle_shp(const Circle_shp& other) : Shape(other)
	{
		circle = Circle_obj(other.circle);
		color = other.color;
	}

	Coordinate Circle_shp::get_center_x() const
	{ return circle.center_x; }

	Coordinate Circle_shp::get_center_y() const
	{ return circle.center_y; }

	Coordinate Circle_shp::get_radius() const
	{ return circle.radius; }

	Color Circle_shp::get_color() const
	{ return color; }

	void Circle_shp::write(std::ostream& os) const
	{
		os << CIRCLE_NAME << " "
		   << circle << " "
		   << color;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Circle_shp& circle)
	{
		circle.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Circle_shp& circle)
	{
		is >> circle.circle
		   >> circle.color;
		return is;
	}
}