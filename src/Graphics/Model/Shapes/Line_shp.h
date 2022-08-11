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
		Coordinate a{};
		Coordinate b{};
		Coordinate c{};
		Color color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Line_shp() = default;
		Line_shp(const Coordinate& a,
				 const Coordinate& b,
				 const Coordinate& c,
				 Color col = DEFAULT_PLOT_COLOR);
		Line_shp(const Line_shp& other);

		// other constructors
		/*!
		 * Constructs the line containing the given segment
		 */
		explicit Line_shp(const Segment_shp& segment,
						  Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs the line containing the two given points
		 */
		Line_shp(const Point_shp& point1,
				 const Point_shp& point2,
				 Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs the line containing the two points p1 and p2\n
		 * where p1 has coordinate (x1, y1) and p2 (x2, y2)
		 */
		Line_shp(const Coordinate& x1,
				 const Coordinate& y1,
				 const Coordinate& x2,
				 const Coordinate& y2,
				 Color col = DEFAULT_PLOT_COLOR);

		~Line_shp() = default;

		Coordinate get_a() const;
		Coordinate get_b() const;
		Coordinate get_c() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;

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
		this-> a = Coordinate(a);
		this-> b = Coordinate(b);
		this-> c = Coordinate(c);
		color = col;
	}

	Line_shp::Line_shp(const Line_shp& other) : Shape(other)
	{
		a = Coordinate(other.a);
		b = Coordinate(other.b);
		c = Coordinate(other.c);
		color = other.color;
	}

	Line_shp::Line_shp(const Segment_shp& segment,
					   Color col)
	{
		Coordinate x1 = segment.get_origin().get_abscissa();
		Coordinate y1 = segment.get_origin().get_ordinate();
		Coordinate x2 = segment.get_destination().get_abscissa();
		Coordinate y2 = segment.get_destination().get_ordinate();
		aux_constructor(x1, y1, x2, y2, col);
	}

	Line_shp::Line_shp(const Point_shp& point1,
					   const Point_shp& point2,
					   Color col)
	{
		Coordinate x1 = point1.get_abscissa();
		Coordinate y1 = point1.get_ordinate();
		Coordinate x2 = point2.get_abscissa();
		Coordinate y2 = point2.get_ordinate();
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
	{ return a; }

	Coordinate Line_shp::get_b() const
	{ return b; }

	Coordinate Line_shp::get_c() const
	{ return c; }

	Color Line_shp::get_color() const
	{ return color; }

	void Line_shp::aux_constructor(const Coordinate& x1,
								   const Coordinate& y1,
								   const Coordinate& x2,
								   const Coordinate& y2,
								   Color col)
	{
		a = y2 - y1;
		b = x1 - x2;
		c = - a * x1 - b * y1;
		color = col;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Line_shp& line)
	{
		os << LINE_NAME << " "
		   << line.get_a() << " "
		   << line.get_b() << " "
		   << line.get_c();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Line_shp& line)
	{
		is >> line.a
		   >> line.b
		   >> line.c;
		return is;
	}
}