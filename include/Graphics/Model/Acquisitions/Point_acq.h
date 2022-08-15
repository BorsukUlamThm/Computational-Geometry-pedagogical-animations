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
}