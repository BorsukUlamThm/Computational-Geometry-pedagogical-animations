#pragma once

#include "Geometric_object.h"


namespace graphics
{
	/*!
	 * A Bounding_box is the smallest rectangle that contains a set of Shape
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
		Bounding_box(const Coordinate& x_min,
					 const Coordinate& x_max,
					 const Coordinate& y_min,
					 const Coordinate& y_max);
		Bounding_box(const Bounding_box& other);

		explicit Bounding_box(const Point_obj& point);
		explicit Bounding_box(const Segment_obj& segment);
		explicit Bounding_box(const Circle_obj& circle);
		explicit Bounding_box(const Polygon_obj& polygon);

		void extend(const Coordinate& x,
					const Coordinate& y);
		void extend(const Bounding_box& other);
		void clear();

		Coordinate get_min_abscissa() const;
		Coordinate get_max_abscissa() const;
		Coordinate get_min_ordinate() const;
		Coordinate get_max_ordinate() const;
	};
}