#pragma once

#include "Plots/Plot.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * This class represent the smallest rectangle needed to contain
	 * a set of plots
	 */
	class Bounding_box
	{
	private:
		Coordinate min_abscissa = MAX_COORDINATE;
		Coordinate max_abscissa = MIN_COORDINATE;
		Coordinate min_ordinate = MAX_COORDINATE;
		Coordinate max_ordinate = MIN_COORDINATE;

	public:
		Bounding_box() = default;
		Bounding_box(const Bounding_box& other);

		void extend(const Point_plot& point);
		void extend(const Segment_plot& segment);
		void extend(const Vector_plot& vector);
		void extend(const Polygon_plot& polygon);
		void extend(const Circle_plot& circle);
		void extend(const Line_plot& line);
		void extend(const Text_plot& text);
		void clear();

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Bounding_box::Bounding_box(const Bounding_box& other)
	{
		min_abscissa = Coordinate(other.min_abscissa);
		max_abscissa = Coordinate(other.max_abscissa);
		min_ordinate = Coordinate(other.min_ordinate);
		max_ordinate = Coordinate(other.max_ordinate);
	}

	void Bounding_box::extend(const Point_plot& point)
	{
		min_abscissa = std::min(min_abscissa, point.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, point.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, point.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, point.get_max_ordinate());
	}

	void Bounding_box::extend(const Segment_plot& segment)
	{
		min_abscissa = std::min(min_abscissa, segment.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, segment.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, segment.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, segment.get_max_ordinate());
	}

	void Bounding_box::extend(const Vector_plot& vector)
	{
		min_abscissa = std::min(min_abscissa, vector.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, vector.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, vector.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, vector.get_max_ordinate());
	}

	void Bounding_box::extend(const Polygon_plot& polygon)
	{
		min_abscissa = std::min(min_abscissa, polygon.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, polygon.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, polygon.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, polygon.get_max_ordinate());
	}

	void Bounding_box::extend(const Circle_plot& circle)
	{
		min_abscissa = std::min(min_abscissa, circle.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, circle.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, circle.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, circle.get_max_ordinate());
	}

	void Bounding_box::extend(const Line_plot& line)
	{/* Nothing to do but to be sure i let it in a comment
    min_abscissa = std::min(min_abscissa, line.get_min_abscissa());
    max_abscissa = std::max(max_abscissa, line.get_max_abscissa());
    min_ordinate = std::min(min_ordinate, line.get_min_ordinate());
    max_ordinate = std::max(max_ordinate, line.get_max_ordinate());*/
	}

	void Bounding_box::extend(const Text_plot& text)
	{
		min_abscissa = std::min(min_abscissa, text.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, text.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, text.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, text.get_max_ordinate());
	}

	void Bounding_box::clear()
	{
		min_abscissa = MAX_COORDINATE;
		max_abscissa = MIN_COORDINATE;
		min_ordinate = MAX_COORDINATE;
		max_ordinate = MIN_COORDINATE;
	}

	Coordinate Bounding_box::get_min_abscissa() const
	{
		return min_abscissa;
	}

	Coordinate Bounding_box::get_max_abscissa() const
	{
		return max_abscissa;
	}

	Coordinate Bounding_box::get_min_ordinate() const
	{
		return min_ordinate;
	}

	Coordinate Bounding_box::get_max_ordinate() const
	{
		return max_ordinate;
	}
}