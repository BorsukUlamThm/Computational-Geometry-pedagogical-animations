#pragma once

#include "Acquisition.h"


namespace graphics
{
	class Segment_acq : public Acquisition
	{
	private:
		Color line_color = DEFAULT_SHAPE_COLOR;
		Color endpoints_color = DEFAULT_SHAPE_COLOR;

		Coordinate tmp_origin_x = 0;
		Coordinate tmp_origin_y = 0;

	public:
		explicit Segment_acq(unsigned nb_segments = -1,
							 Color line_col = DEFAULT_SHAPE_COLOR,
							 Color endpoints_col = DEFAULT_SHAPE_COLOR);

		State starting_state() const override;
		Color get_line_color() const;
		Color get_endpoints_color() const;

		void add_segment(const Coordinate& ogn_x,
						 const Coordinate& ogn_y,
						 const Coordinate& dst_x,
						 const Coordinate& dst_y);
		void add_origin(const Coordinate& ogn_x,
						const Coordinate& ogn_y);
		void add_destination(const Coordinate& dst_x,
							 const Coordinate& dst_y);
	};
}