#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Segment_shp.h"


namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a line\n
	 * \n
	 * -> parameters a b and c such that the line
	 *    has equation ax + by + c = 0\n
	 * -> color\n
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

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Line_shp& line);

	private:
		void aux_constructor(const Coordinate& x1,
							 const Coordinate& y1,
							 const Coordinate& x2,
							 const Coordinate& y2,
							 Color col);
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

	Line_shp::Line_shp(const Line_shp& other)
	{
		a = Coordinate(other.a);
		b = Coordinate(other.b);
		c = Coordinate(other.c);
		color = other.color;
	}

	Coordinate Line_shp::get_a() const
	{
		return a;
	}

	Coordinate Line_shp::get_b() const
	{
		return b;
	}

	Coordinate Line_shp::get_c() const
	{
		return c;
	}

	Color Line_shp::get_color() const
	{
		return color;
	}

	Coordinate Line_shp::get_min_abscissa() const
	{
		return MAX_COORDINATE;
	}

	Coordinate Line_shp::get_max_abscissa() const
	{
		return MIN_COORDINATE;
	}

	Coordinate Line_shp::get_min_ordinate() const
	{
		return MAX_COORDINATE;
	}

	Coordinate Line_shp::get_max_ordinate() const
	{
		return MIN_COORDINATE;
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