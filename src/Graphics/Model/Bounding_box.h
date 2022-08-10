#pragma once

#include "Shapes/Shape.h"


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

		void extend(const Shape& plot);
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

	void Bounding_box::extend(const Shape& plot)
	{
		min_abscissa = std::min(min_abscissa, plot.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, plot.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, plot.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, plot.get_max_ordinate());
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