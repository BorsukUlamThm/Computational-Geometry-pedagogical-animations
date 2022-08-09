#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Global_variables.h"


namespace gr
{
	class Segment_acq
	{
	private:
		Color line_color = DEFAULT_PLOT_COLOR;
		Color end_points_color = DEFAULT_PLOT_COLOR;

	public:
		Segment_acq() = default;
		explicit Segment_acq(Color line_col,
												 Color end_points_col = DEFAULT_PLOT_COLOR);
		Segment_acq(const Segment_acq& other);
		~Segment_acq() = default;

		Color get_line_color() const;
		Color get_end_points_color() const;
	};

	Segment_acq::Segment_acq(Color line_col,
													 Color end_points_col)
	{
		line_color = line_col;
		end_points_color = end_points_col;
	}

	Segment_acq::Segment_acq(const Segment_acq& other)
	{
		line_color = other.line_color;
		end_points_color = other.end_points_color;
	}

	Color Segment_acq::get_line_color() const
	{
		return line_color;
	}

	Color Segment_acq::get_end_points_color() const
	{
		return end_points_color;
	}
}
