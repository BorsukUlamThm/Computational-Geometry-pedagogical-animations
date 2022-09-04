#pragma once

#include <iostream>
#include <vector>
#include "graphics/model/global_variables.h"


namespace graphics
{
	struct Geometric_object
	{
		virtual ~Geometric_object() = default;
	};

	struct Point_obj : public Geometric_object
	{
		Coordinate abscissa = 0;
		Coordinate ordinate = 0;

		Point_obj() = default;
		Point_obj(const Coordinate& x,
				  const Coordinate& y);
	};

	struct Segment_obj : public Geometric_object
	{
		Point_obj origin;
		Point_obj destination;

		Segment_obj() = default;
		Segment_obj(const Point_obj& ogn,
					const Point_obj& dst);
		Segment_obj(const Coordinate& ogn_x,
					const Coordinate& ogn_y,
					const Coordinate& dst_x,
					const Coordinate& dst_y);
	};

	struct Circle_obj : Geometric_object
	{
		Coordinate center_x = 0;
		Coordinate center_y = 0;
		Coordinate radius = 0;

		Circle_obj() = default;
		Circle_obj(const Coordinate& x,
				   const Coordinate& y,
				   const Coordinate& rad);
	};

	typedef std::vector<Point_obj> Polygon_obj;

	struct Line_obj : Geometric_object
	{
		// line defined by the equation ax + by + c = 0
		Coordinate param_a = 1;
		Coordinate param_b = -1;
		Coordinate param_c = 0;

		Line_obj() = default;

		Line_obj(const Coordinate& a,
				 const Coordinate& b,
				 const Coordinate& c);
		Line_obj(const Coordinate& x1,
				 const Coordinate& y1,
				 const Coordinate& x2,
				 const Coordinate& y2);
		Line_obj(const Point_obj& point1,
				 const Point_obj& point2);
		explicit Line_obj(const Segment_obj& segment);
	};

	std::ostream& operator<<(std::ostream& os,
							 const Point_obj& point);
	std::ostream& operator<<(std::ostream& os,
							 const Segment_obj& segment);
	std::ostream& operator<<(std::ostream& os,
							 const Circle_obj& circle);
	std::ostream& operator<<(std::ostream& os,
							 const Line_obj& line);

	std::istream& operator>>(std::istream& is,
							 Point_obj& point);
	std::istream& operator>>(std::istream& is,
							 Segment_obj& segment);
	std::istream& operator>>(std::istream& is,
							 Circle_obj& circle);
	std::istream& operator>>(std::istream& is,
							 Line_obj& line);
}