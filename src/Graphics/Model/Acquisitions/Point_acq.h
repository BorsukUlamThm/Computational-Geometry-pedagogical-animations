#pragma once

#include "Acquisition.h"


namespace graphics
{
	class Point_acq : public Acquisition
	{
	private:
		Color color = DEFAULT_SHAPE_COLOR;
		float radius = 3;

	public:
		explicit Point_acq(unsigned nb_points = -1,
						   Color col = DEFAULT_SHAPE_COLOR,
						   float rad = 3);

		State starting_state() const override;
		Color get_color() const;
		float get_radius() const;

		void add_point(const Coordinate& x,
					   const Coordinate& y);
	};

	Point_acq::Point_acq(unsigned nb_points,
						 Color col,
						 float rad)
	{
		nb_acquisitions = nb_points;
		color = col;
		radius = rad;
	}

	State Point_acq::starting_state() const
	{ return POINT_ACQ1; }

	Color Point_acq::get_color() const
	{ return color; }

	float Point_acq::get_radius() const
	{ return radius; }

	void Point_acq::add_point(const Coordinate& x,
							  const Coordinate& y)
	{
		Acquired_shape_ptr point = std::make_shared<Acquired_point>(x, y);
		acquired_shapes.emplace_back(point);
	}
}