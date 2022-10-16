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

	struct Polygon_obj : Geometric_object
	{
		typedef std::vector<Point_obj> Vertices;

		Vertices vertices {};

		Polygon_obj() = default;

		const Point_obj& operator[](unsigned i) const
		{ return vertices[i]; }
		Point_obj& operator[](unsigned i)
		{ return vertices[i]; }
		unsigned size() const
		{ return vertices.size(); }

		void push_back(const Point_obj& point)
		{ vertices.push_back(point); }
		void emplace_back(const Coordinate& x,
						  const Coordinate& y)
		{ vertices.emplace_back(x, y); }
		void clear()
		{ vertices.clear(); }

		Vertices::const_iterator begin() const
		{ return vertices.begin(); }
		Vertices::const_iterator end() const
		{ return vertices.end(); }
	};


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