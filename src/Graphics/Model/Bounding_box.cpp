#include "Graphics/Model/Bounding_box.h"


namespace graphics
{
	Bounding_box::Bounding_box(const Coordinate& x_min,
							   const Coordinate& x_max,
							   const Coordinate& y_min,
							   const Coordinate& y_max)
	{
		min_abscissa = Coordinate(x_min);
		max_abscissa = Coordinate(x_max);
		min_ordinate = Coordinate(y_min);
		max_ordinate = Coordinate(y_max);
	}

	Bounding_box::Bounding_box(const Bounding_box& other)
	{
		min_abscissa = Coordinate(other.min_abscissa);
		max_abscissa = Coordinate(other.max_abscissa);
		min_ordinate = Coordinate(other.min_ordinate);
		max_ordinate = Coordinate(other.max_ordinate);
	}

	Bounding_box::Bounding_box(const Point_obj& point)
	{
		min_abscissa = Coordinate(point.abscissa);
		max_abscissa = Coordinate(point.abscissa);
		min_ordinate = Coordinate(point.ordinate);
		max_ordinate = Coordinate(point.ordinate);
	}

	Bounding_box::Bounding_box(const Segment_obj& segment)
	{
		min_abscissa = std::min(segment.origin_x, segment.destination_x);
		max_abscissa = std::max(segment.origin_x, segment.destination_x);
		min_ordinate = std::min(segment.origin_y, segment.destination_y);
		max_ordinate = std::max(segment.origin_y, segment.destination_y);
	}

	Bounding_box::Bounding_box(const Circle_obj& circle)
	{
		min_abscissa = circle.center_x - circle.radius;
		max_abscissa = circle.center_x + circle.radius;
		min_ordinate = circle.center_y - circle.radius;
		min_ordinate = circle.center_y + circle.radius;
	}

	Bounding_box::Bounding_box(const Polygon_obj& polygon)
	{
		for (auto& point : polygon)
		{
			extend(point.abscissa, point.ordinate);
		}
	}

	void Bounding_box::extend(const Coordinate& x, const Coordinate& y)
	{
		min_abscissa = std::min(min_abscissa, x);
		max_abscissa = std::max(max_abscissa, x);
		min_ordinate = std::min(min_ordinate, y);
		max_ordinate = std::max(max_ordinate, y);
	}

	void Bounding_box::extend(const Bounding_box& other)
	{
		min_abscissa = std::min(min_abscissa, other.get_min_abscissa());
		max_abscissa = std::max(max_abscissa, other.get_max_abscissa());
		min_ordinate = std::min(min_ordinate, other.get_min_ordinate());
		max_ordinate = std::max(max_ordinate, other.get_max_ordinate());
	}

	void Bounding_box::clear()
	{
		min_abscissa = MAX_COORDINATE;
		max_abscissa = MIN_COORDINATE;
		min_ordinate = MAX_COORDINATE;
		max_ordinate = MIN_COORDINATE;
	}

	Coordinate Bounding_box::get_min_abscissa() const
	{ return min_abscissa; }

	Coordinate Bounding_box::get_max_abscissa() const
	{ return max_abscissa; }

	Coordinate Bounding_box::get_min_ordinate() const
	{ return min_ordinate; }

	Coordinate Bounding_box::get_max_ordinate() const
	{ return max_ordinate; }
}