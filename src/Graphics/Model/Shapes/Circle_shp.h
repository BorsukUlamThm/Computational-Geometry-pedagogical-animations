#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Shape.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Circle_shp is a circle drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The x y coordinates of the center of the represented circle
	 * - The radius of the represented circle
	 * - The color of the circle on the Canvas
	 *
	 * Note that the x y coordinate are the cartesian coordinate of the abstract
	 * circle center, not its position on the Canvas in pixel\n
	 * In the same way, the radius it the radius of the abstract circle, and not
	 * the radius of the circle drawn on the canvas\n
	 */
	class Circle_shp : public Shape
	{
	private:
		Coordinate center_x {};
		Coordinate center_y {};
		Coordinate radius {};
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		Circle_shp();
		Circle_shp(const Coordinate& x,
				   const Coordinate& y,
				   const Coordinate& rad,
				   Color col = DEFAULT_SHAPE_COLOR);
		Circle_shp(const Circle_shp& other);

		~Circle_shp() = default;

		Coordinate get_center_x() const;
		Coordinate get_center_y() const;
		Coordinate get_radius() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;

	private:
		void make_bounding_box();

	public:
		friend std::istream& operator>>(std::istream& is,
										Circle_shp& circle);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Circle_shp::Circle_shp()
	{
		make_bounding_box();
	}

	Circle_shp::Circle_shp(const Coordinate& x,
						   const Coordinate& y,
						   const Coordinate& rad,
						   Color col)
	{
		center_x = Coordinate(x);
		center_y = Coordinate(y);
		radius = Coordinate(rad);
		color = col;

		make_bounding_box();
	}

	Circle_shp::Circle_shp(const Circle_shp& other) : Shape(other)
	{
		center_x = Coordinate(other.center_x);
		center_y = Coordinate(other.center_y);
		radius = Coordinate(other.radius);
		color = other.color;
	}

	Coordinate Circle_shp::get_center_x() const
	{ return center_x; }

	Coordinate Circle_shp::get_center_y() const
	{ return center_y; }

	Coordinate Circle_shp::get_radius() const
	{ return radius; }

	Color Circle_shp::get_color() const
	{ return color; }

	void Circle_shp::make_bounding_box()
	{
		Coordinate x_min = center_x - radius;
		Coordinate x_max = center_x + radius;
		Coordinate y_min = center_y - radius;
		Coordinate y_max = center_y + radius;

		bounding_box = Bounding_box(x_min, x_max, y_min, y_max);
	}

	std::ostream& operator<<(std::ostream& os,
							 const Circle_shp& circle)
	{
		os << CIRCLE_NAME << " "
		   << circle.get_center_x() << " "
		   << circle.get_center_y() << " "
		   << circle.get_radius();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Circle_shp& circle)
	{
		is >> circle.center_x
		   >> circle.center_y
		   >> circle.radius;
		return is;
	}
}