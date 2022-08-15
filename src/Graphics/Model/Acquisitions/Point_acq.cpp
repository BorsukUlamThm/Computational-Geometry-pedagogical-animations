#include "Graphics/Model/Acquisitions/Point_acq.h"


namespace graphics
{
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
		Geometric_object_ptr point = std::make_shared<Point_obj>(x, y);
		acquired_shapes.emplace_back(point);
	}
}