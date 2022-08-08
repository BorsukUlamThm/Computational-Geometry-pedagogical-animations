#pragma once

#include "Point_plt.h"


namespace gr
{
	//! [Jd] Point_plt class
	/**
	 * [Jd] description of Point_plt
	 */
	class Segment_plt
	{
	private:
		Point_plt origin; /**< member abscissa */
		Point_plt destination; /**< member abscissa */
		Color line_color = DEFAULT_PLOT_COLOR;

	public:
		Segment_plt() = default;
		//* [jd] constructor
		/**
		 * description
		 * @param ogn aze
		 * @param dst aze
		 * @param line_col aze
		 */
		Segment_plt(const Point_plt& ogn, const Point_plt& dst,
								Color line_col = DEFAULT_PLOT_COLOR);
		Segment_plt(const Coordinate& ogn_x, const Coordinate& ogn_y,
								const Coordinate& dst_x, const Coordinate& dst_y,
								Color line_col = DEFAULT_PLOT_COLOR,
								Color end_points_col = DEFAULT_PLOT_COLOR);
		Segment_plt(const Segment_plt& other);
		~Segment_plt() = default;

		/**
		 * aze
		 * @return aze
		 */
		Point_plt get_origin() const;
		Point_plt get_destination() const;
		Color get_line_color() const;

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;

		friend std::istream& operator>>(std::istream& is, Segment_plt& segment);
	};

	Segment_plt::Segment_plt(const Point_plt& ogn, const Point_plt& dst,
													 Color line_col)
	{
		origin = Point_plt(ogn);
		destination = Point_plt(dst);
		line_color = line_col;
	}

	Segment_plt::Segment_plt(const Coordinate& ogn_x, const Coordinate& ogn_y,
													 const Coordinate& dst_x, const Coordinate& dst_y,
													 Color line_col, Color end_points_col)
	{
		origin = Point_plt(ogn_x, ogn_y, end_points_col);
		destination = Point_plt(dst_x, dst_y, end_points_col);
		line_color = line_col;
	}

	Segment_plt::Segment_plt(const Segment_plt& other)
	{
		origin = Point_plt(other.origin);
		destination = Point_plt(other.destination);
		line_color = other.line_color;
	}

	Point_plt Segment_plt::get_origin() const
	{
		return origin;
	}

	Point_plt Segment_plt::get_destination() const
	{
		return destination;
	}

	Color Segment_plt::get_line_color() const
	{
		return line_color;
	}

	Coordinate Segment_plt::get_min_abscissa() const
	{
		return std::min(origin.get_min_abscissa(),
										destination.get_min_abscissa());
	}

	Coordinate Segment_plt::get_max_abscissa() const
	{
		return std::max(origin.get_max_abscissa(),
										destination.get_max_abscissa());
	}

	Coordinate Segment_plt::get_min_ordinate() const
	{
		return std::min(origin.get_min_ordinate(),
										destination.get_min_ordinate());
	}

	Coordinate Segment_plt::get_max_ordinate() const
	{
		return std::max(origin.get_max_ordinate(),
										destination.get_max_ordinate());
	}

	std::ostream& operator<<(std::ostream& os, const Segment_plt& segment)
	{
		os << SEGMENT_NAME << " " << segment.get_origin()
			 << " " << segment.get_destination();
		return os;
	}

	std::istream& operator>>(std::istream& is, Segment_plt& segment)
	{
		std::string dummy;
		is >> dummy;
		is >> segment.origin;
		is >> dummy;
		is >> segment.destination;
		return is;
	}
}