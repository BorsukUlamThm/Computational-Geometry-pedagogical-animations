#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Global_variables.h"


namespace gr
{
	//! [Qt] Point_plt class
	/*!
	 * [Qt] description of Point_plt
	 */
	class Point_plt
	{
	private:
		Coordinate abscissa{}; /*!< member abscissa */
		Coordinate ordinate{}; /*!< member ordinate */
		Color color = DEFAULT_PLOT_COLOR; /*!< member color */
		float radius = 3; /*!< member radius */

	public:
		Point_plt() = default;
		//! [Qt] constructor
		/*!
		 * description of the constructor
		 * @param x desc of x
		 * @param y desc of y
		 * @param col desc of col
		 * @param rad desc of rad
		 */
		Point_plt(const Coordinate& x, const Coordinate& y,
							Color col = DEFAULT_PLOT_COLOR, float rad = 3);
		Point_plt(const Point_plt& other);
		~Point_plt() = default;

		//! [Qt] get_abscissa
		/*!
		 * desc of get_abscissa
		 * @return the return value
		 */
		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		Color get_color() const;
		float get_radius() const;

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;

		friend std::istream& operator>>(std::istream& is, Point_plt& point);
	};

	Point_plt::Point_plt(const Coordinate &x, const Coordinate &y,
											 Color col, float rad)
	{
		abscissa = Coordinate(x);
		ordinate = Coordinate(y);
		color = col;
		radius = rad;
	}

	Point_plt::Point_plt(const Point_plt& other)
	{
		abscissa = Coordinate(other.abscissa);
		ordinate = Coordinate(other.ordinate);
		color = other.color;
		radius = other.radius;
	}

	Coordinate Point_plt::get_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plt::get_ordinate() const
	{
		return ordinate;
	}

	Color Point_plt::get_color() const
	{
		return color;
	}

	float Point_plt::get_radius() const
	{
		return radius;
	}

	Coordinate Point_plt::get_min_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plt::get_max_abscissa() const
	{
		return abscissa;
	}

	Coordinate Point_plt::get_min_ordinate() const
	{
		return ordinate;
	}

	Coordinate Point_plt::get_max_ordinate() const
	{
		return ordinate;
	}

	std::ostream& operator<<(std::ostream& os, const Point_plt& point)
	{
		os << POINT_NAME << " " << point.get_abscissa()
			 << " " << point.get_ordinate();
		return os;
	}

	std::istream& operator>>(std::istream& is, Point_plt& point)
	{
		is >> point.abscissa >> point.ordinate;
		return is;
	}
}