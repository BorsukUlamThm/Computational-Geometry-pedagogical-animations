#pragma once

#include "Point_plot.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a circle\n
	 * \n
	 * -> endpoints of the segment\n
	 * -> color
	 */
	class Segment_plot
	{
	private:
		Point_plot origin;
		Point_plot destination;
		Color line_color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Segment_plot() = default;
		Segment_plot(const Point_plot& ogn,
					 const Point_plot& dst,
					 Color line_col = DEFAULT_PLOT_COLOR);
		Segment_plot(const Segment_plot& other);

		// other constructor
		/*!
		 * Constructs the segment whose endpoints are ogn and dst\n
		 * where ogn coordinate (ogn_x, ogn_y) and dst (dst_x, dst_y)
		 */
		Segment_plot(const Coordinate& ogn_x,
					 const Coordinate& ogn_y,
					 const Coordinate& dst_x,
					 const Coordinate& dst_y,
					 Color line_col = DEFAULT_PLOT_COLOR,
					 Color end_points_col = DEFAULT_PLOT_COLOR);

		~Segment_plot() = default;

		Point_plot get_origin() const;
		Point_plot get_destination() const;
		Color get_line_color() const;

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;

		friend std::istream& operator>>(std::istream& is,
										Segment_plot& segment);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Segment_plot::Segment_plot(const Point_plot& ogn,
							   const Point_plot& dst,
							   Color line_col)
	{
		origin = Point_plot(ogn);
		destination = Point_plot(dst);
		line_color = line_col;
	}

	Segment_plot::Segment_plot(const Coordinate& ogn_x,
							   const Coordinate& ogn_y,
							   const Coordinate& dst_x,
							   const Coordinate& dst_y,
							   Color line_col,
							   Color end_points_col)
	{
		origin = Point_plot(ogn_x, ogn_y, end_points_col);
		destination = Point_plot(dst_x, dst_y, end_points_col);
		line_color = line_col;
	}

	Segment_plot::Segment_plot(const Segment_plot& other)
	{
		origin = Point_plot(other.origin);
		destination = Point_plot(other.destination);
		line_color = other.line_color;
	}

	Point_plot Segment_plot::get_origin() const
	{
		return origin;
	}

	Point_plot Segment_plot::get_destination() const
	{
		return destination;
	}

	Color Segment_plot::get_line_color() const
	{
		return line_color;
	}

	Coordinate Segment_plot::get_min_abscissa() const
	{
		return std::min(origin.get_min_abscissa(),
						destination.get_min_abscissa());
	}

	Coordinate Segment_plot::get_max_abscissa() const
	{
		return std::max(origin.get_max_abscissa(),
						destination.get_max_abscissa());
	}

	Coordinate Segment_plot::get_min_ordinate() const
	{
		return std::min(origin.get_min_ordinate(),
						destination.get_min_ordinate());
	}

	Coordinate Segment_plot::get_max_ordinate() const
	{
		return std::max(origin.get_max_ordinate(),
						destination.get_max_ordinate());
	}

	std::ostream& operator<<(std::ostream& os,
							 const Segment_plot& segment)
	{
		os << SEGMENT_NAME << " "
		   << segment.get_origin() << " "
		   << segment.get_destination();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Segment_plot& segment)
	{
		std::string dummy;
		is >> dummy
		   >> segment.origin
		   >> dummy
		   >> segment.destination;
		return is;
	}
}