#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Shape.h"


namespace graphics
{
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

	std::ostream& operator<<(std::ostream& os,
							 const Line_shp& line);
	std::istream& operator>>(std::istream& is,
							 Line_shp& line);
}