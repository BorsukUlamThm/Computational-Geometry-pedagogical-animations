#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Segment_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Line_shp is a line with equation ax + by + c = 0 drawn on a Canvas\n
	 * It is defined by\n
	 *
	 * - The three numbers a, b, c
	 * - The color of the line on the Canvas
	 */
	class Line_shp : public Shape
	{
	private:
		Line_obj line;
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Line_shp() = default;
		Line_shp(const Coordinate& a,
				 const Coordinate& b,
				 const Coordinate& c,
				 Color col = DEFAULT_SHAPE_COLOR);
		Line_shp(const Line_shp& other);

		// other constructors
		/*!
		 * Constructs the line containing the given segment
		 */
		explicit Line_shp(const Segment_obj& segment,
						  Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs the line containing the two given points
		 */
		Line_shp(const Point_obj& point1,
				 const Point_obj& point2,
				 Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs the line containing the two points p1 and p2\n
		 * where p1 has coordinate (x1, y1) and p2 (x2, y2)
		 */
		Line_shp(const Coordinate& x1,
				 const Coordinate& y1,
				 const Coordinate& x2,
				 const Coordinate& y2,
				 Color col = DEFAULT_SHAPE_COLOR);

		~Line_shp() = default;

		Coordinate get_a() const;
		Coordinate get_b() const;
		Coordinate get_c() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	private:
		// no need to have a make_bounding_box here
		// since the line is unbounded

		void aux_constructor(const Coordinate& x1,
							 const Coordinate& y1,
							 const Coordinate& x2,
							 const Coordinate& y2,
							 Color col);

	public:
		friend std::istream& operator>>(std::istream& is,
										Line_shp& line);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Line_shp::Line_shp(const Coordinate& a,
					   const Coordinate& b,
					   const Coordinate& c,
					   Color col)
	{
		line = Line_obj(a, b, c);
		color = col;
	}

	Line_shp::Line_shp(const Line_shp& other) : Shape(other)
	{
		line = Line_obj(other.line);
		color = other.color;
	}

	Line_shp::Line_shp(const Segment_obj& segment,
					   Color col)
	{
		Coordinate ogn_x = segment.origin_x;
		Coordinate ogn_y = segment.origin_y;
		Coordinate dst_x = segment.destination_x;
		Coordinate dst_y = segment.destination_y;
		aux_constructor(ogn_x, ogn_y, dst_x, dst_y, col);
	}

	Line_shp::Line_shp(const Point_obj& point1,
					   const Point_obj& point2,
					   Color col)
	{
		Coordinate x1 = point1.abscissa;
		Coordinate y1 = point1.ordinate;
		Coordinate x2 = point2.abscissa;
		Coordinate y2 = point2.ordinate;
		aux_constructor(x1, y1, x2, y2, col);
	}

	Line_shp::Line_shp(const Coordinate& x1,
					   const Coordinate& y1,
					   const Coordinate& x2,
					   const Coordinate& y2,
					   Color col)
	{
		aux_constructor(x1, y1, x2, y2, col);
	}

	Coordinate Line_shp::get_a() const
	{ return line.a; }

	Coordinate Line_shp::get_b() const
	{ return line.b; }

	Coordinate Line_shp::get_c() const
	{ return line.c; }

	Color Line_shp::get_color() const
	{ return color; }

	void Line_shp::write(std::ostream& os) const
	{
		os << LINE_NAME << " "
		   << line.a << " "
		   << line.b << " "
		   << line.c << " "
		   << color;
	}

	void Line_shp::aux_constructor(const Coordinate& x1,
								   const Coordinate& y1,
								   const Coordinate& x2,
								   const Coordinate& y2,
								   Color col)
	{
		line.a = y2 - y1;
		line.b = x1 - x2;
		line.c = -line.a * x1 - line.b * y1;
		color = col;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Line_shp& line)
	{
		line.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Line_shp& line)
	{
		is >> line.line.a
		   >> line.line.b
		   >> line.line.c
		   >> line.color;
		return is;
	}
}