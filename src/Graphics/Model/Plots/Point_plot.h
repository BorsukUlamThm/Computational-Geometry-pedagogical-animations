#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Global_variables.h"


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
	class Point_plot
	{
	private:
		Coordinate abscissa{};
		Coordinate ordinate{};
		Color color = DEFAULT_PLOT_COLOR;
		float radius = 3;

	public:
		Point_plot() = default;
		Point_plot(const Coordinate& x,
				   const Coordinate& y,
				   Color col = DEFAULT_PLOT_COLOR,
				   float rad = 3);
		Point_plot(const Point_plot& other);

		~Point_plot() = default;

		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		Color get_color() const;
		float get_radius() const;

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;

		friend std::istream& operator>>(std::istream& is,
										Point_plot& point);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Point_plot::Point_plot(const Coordinate &x,
						   const Coordinate &y,
						   Color col,
						   float rad)
	{
		abscissa = Coordinate(x);
		ordinate = Coordinate(y);
		color = col;
		radius = rad;
	}

	Point_plot::Point_plot(const Point_plot& other)
	{
		abscissa = Coordinate(other.abscissa);
		ordinate = Coordinate(other.ordinate);
		color = other.color;
		radius = other.radius;
	}

	Coordinate Point_plot::get_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plot::get_ordinate() const
	{
		return ordinate;
	}

	Color Point_plot::get_color() const
	{
		return color;
	}

	float Point_plot::get_radius() const
	{
		return radius;
	}

	Coordinate Point_plot::get_min_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plot::get_max_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plot::get_min_ordinate() const
	{
		return ordinate;
	}

	Coordinate Point_plot::get_max_ordinate() const
	{
		return ordinate;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Point_plot& point)
	{
		os << POINT_NAME << " "
		   << point.get_abscissa() << " "
		   << point.get_ordinate();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Point_plot& point)
	{
		is >> point.abscissa
		   >> point.ordinate;
		return is;
	}
}