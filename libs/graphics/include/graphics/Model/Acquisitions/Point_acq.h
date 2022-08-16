#pragma once

#include "Acquisition.h"


namespace graphics
{
	/*!
	 * A Point_acq is an Acquisition of points. It is defined by the color and
	 * radius of the drawn points during the acquisition
	 */
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
}