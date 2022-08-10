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
	 * Contains the needed information to draw a circle\n
	 * \n
	 * -> x y coordinates of the center\n
	 * -> radius\n
	 * -> color\n
	 */
	class Circle_shp : public Shape
	{
	private:
		Coordinate center_x{};
		Coordinate center_y{};
		Coordinate radius{};
		Color color = DEFAULT_PLOT_COLOR;

	public:
		Circle_shp() = default;
		Circle_shp(const Coordinate& x,
				   const Coordinate& y,
				   const Coordinate& rad,
				   Color col = DEFAULT_PLOT_COLOR);
		Circle_shp(const Circle_shp& other);

		~Circle_shp() = default;

		Coordinate get_center_x() const;
		Coordinate get_center_y() const;
		Coordinate get_radius() const;
		Color get_color() const;

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Circle_shp& circle);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Circle_shp::Circle_shp(const Coordinate& x,
						   const Coordinate& y,
						   const Coordinate& rad,
						   Color col)
	{
		center_x = Coordinate(x);
		center_y = Coordinate(y);
		radius = Coordinate(rad);
		color = col;
	}

	Circle_shp::Circle_shp(const Circle_shp& other)
	{
		center_x = Coordinate(other.center_x);
		center_y = Coordinate(other.center_y);
		radius = Coordinate(other.radius);
		color = other.color;
	}

	Coordinate Circle_shp::get_center_x() const
	{
		return center_x;
	}

	Coordinate Circle_shp::get_center_y() const
	{
		return  center_y;
	}

	Coordinate Circle_shp::get_radius() const
	{
		return radius;
	}

	Color Circle_shp::get_color() const
	{
		return color;
	}

	Coordinate Circle_shp::get_min_abscissa() const
	{
		return center_x - radius;
	}

	Coordinate Circle_shp::get_max_abscissa() const
	{
		return center_x + radius;
	}

	Coordinate Circle_shp::get_min_ordinate() const
	{
		return center_y - radius;
	}

	Coordinate Circle_shp::get_max_ordinate() const
	{
		return center_y + radius;
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