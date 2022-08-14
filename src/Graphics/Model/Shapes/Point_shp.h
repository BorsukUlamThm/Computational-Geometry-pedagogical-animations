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
	 * A Point_shp is a point drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The x y coordinates of the represented point
	 * - The color of the point on the Canvas
	 * - The radius of the point on the Canvas, in pixel
	 *
	 * Note that the x y coordinate are the cartesian coordinate of the abstract
	 * point, not its position on the Canvas in pixel\n
	 */
	class Point_shp : public Shape
	{
	private:
		Point_obj point;
		Color color = DEFAULT_SHAPE_COLOR;
		float radius = 3;

	public:
		Point_shp();
		Point_shp(const Coordinate& x,
				  const Coordinate& y,
				  Color col = DEFAULT_SHAPE_COLOR,
				  float rad = 3);
		Point_shp(const Point_shp& other);

		~Point_shp() = default;

		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		Color get_color() const;
		float get_radius() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	public:
		friend std::istream& operator>>(std::istream& is,
										Point_shp& point);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Point_shp::Point_shp()
	{
		bounding_box = Bounding_box(point);
	}

	Point_shp::Point_shp(const Coordinate& x,
						 const Coordinate& y,
						 Color col,
						 float rad)
	{
		point.abscissa = Coordinate(x);
		point.ordinate = Coordinate(y);
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
		   << point.abscissa << " "
		   << point.ordinate << " "
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
		is >> point.point.abscissa
		   >> point.point.ordinate
		   >> point.color
		   >> point.radius;
		return is;
	}
}