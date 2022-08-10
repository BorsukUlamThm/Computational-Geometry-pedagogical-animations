#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Shape.h"

namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a circle\n
	 * \n
	 * -> abscissa\n
	 * -> ordinate\n
	 * -> color\n
	 * -> radius of the point plot, in pixel\n
	 */
	class Point_shp : public Shape
	{
	private:
		Coordinate abscissa{};
		Coordinate ordinate{};
		Color color = DEFAULT_PLOT_COLOR;
		float radius = 3;

	public:
		Point_shp() = default;
		Point_shp(const Coordinate& x,
				  const Coordinate& y,
				  Color col = DEFAULT_PLOT_COLOR,
				  float rad = 3);
		Point_shp(const Point_shp& other);

		~Point_shp() = default;

		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		Color get_color() const;
		float get_radius() const;

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Point_shp& point);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Point_shp::Point_shp(const Coordinate &x,
						 const Coordinate &y,
						 Color col,
						 float rad)
	{
		abscissa = Coordinate(x);
		ordinate = Coordinate(y);
		color = col;
		radius = rad;
	}

	Point_shp::Point_shp(const Point_shp& other)
	{
		abscissa = Coordinate(other.abscissa);
		ordinate = Coordinate(other.ordinate);
		color = other.color;
		radius = other.radius;
	}

	Coordinate Point_shp::get_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_shp::get_ordinate() const
	{
		return ordinate;
	}

	Color Point_shp::get_color() const
	{
		return color;
	}

	float Point_shp::get_radius() const
	{
		return radius;
	}

	Coordinate Point_shp::get_min_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_shp::get_max_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_shp::get_min_ordinate() const
	{
		return ordinate;
	}

	Coordinate Point_shp::get_max_ordinate() const
	{
		return ordinate;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Point_shp& point)
	{
		os << POINT_NAME << " "
		   << point.get_abscissa() << " "
		   << point.get_ordinate();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Point_shp& point)
	{
		is >> point.abscissa
		   >> point.ordinate;
		return is;
	}
}