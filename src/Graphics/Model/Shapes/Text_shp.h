#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Vector_shp.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * A Text_shape is a text drawn on a Canvas\n
	 * It is designed to add some information about shapes. For example in order
	 * to add a label above a point\n
	 * It is defined by\n
	 *
	 * - A std::string with its content
	 * - The x y coordinate of the place in the plane where the text should be
	 * - The font size on the Canvas
	 * - An offset, in pixel to move the text on the Canvas
	 * - The text color
	 *
	 * For example, if you have a Point_shp point that you wish to label "Foo",
	 * you can use a Text_shp as with content "Foo", the same x y coordinate as
	 * point, and an a y offset large enough to place the text above the point
	 * on the canvas\n
	 * Actually you dont need to do this, you can use the constructor\n
	 * ```C
	 * Text_shp(const std::string& text,
	 *          const Point_shp& point,
	 *          unsigned size = 16,
	 *          const Color col = DEFAULT_SHAPE_COLOR)
	 * ```
	 * which was already designed for this usecase, but it gives you an idea\n
	 */
	class Text_shp : public Shape
	{
	private:
		std::string content {};
		Point_obj point;
		unsigned size = 16;
		float offset_x = 0;
		float offset_y = 0;
		Color color = DEFAULT_SHAPE_COLOR;

	public:
		// standard constructors
		Text_shp();
		Text_shp(const std::string& text,
				 const Coordinate& x,
				 const Coordinate& y,
				 unsigned size = 16,
				 float off_x = 0,
				 float off_y = 0,
				 const Color col = DEFAULT_SHAPE_COLOR);
		Text_shp(const Text_shp& other);

		// other constructors
		/*!
		 * Constructs a text that will be drawn
		 * just above the given point
		 */
		Text_shp(const std::string& text,
				 const Point_shp& point,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs a text that will be drawn
		 * in the middle of the given segment
		 */
		Text_shp(const std::string& text,
				 const Segment_shp& segment,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);
		/*!
		 * Constructs a text that will be drawn
		 * in the middle of the given vector
		 */
		Text_shp(const std::string& text,
				 const Vector_shp& vector,
				 unsigned size = 16,
				 const Color col = DEFAULT_SHAPE_COLOR);

		~Text_shp() = default;

		std::string get_content() const;
		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		unsigned get_size() const;
		float get_offset_x() const;
		float get_offset_y() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;
		void write(std::ostream& os) const override;

	private:
		void aux_constructor(const std::string& text,
							 const Coordinate& x,
							 const Coordinate& y,
							 unsigned size,
							 float off_x,
							 float off_y,
							 Color col);

	public:
		friend std::istream& operator>>(std::istream& is,
										Text_shp& text);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	Text_shp::Text_shp()
	{
		bounding_box = Bounding_box(point);
	}

	Text_shp::Text_shp(const std::string& text,
					   const Coordinate& x,
					   const Coordinate& y,
					   unsigned size,
					   float off_x,
					   float off_y,
					   Color col)
	{
		aux_constructor(text, x, y, size, off_x, off_y, col);
	}

	Text_shp::Text_shp(const Text_shp& other) : Shape(other)
	{
		content = std::string(other.content);
		point.abscissa = Coordinate(other.point.abscissa);
		point.ordinate = Coordinate(other.point.ordinate);
		size = other.size;
		offset_x = other.offset_x;
		offset_y = other.offset_y;
		color = other.color;
	}

	Text_shp::Text_shp(const std::string& text,
					   const Point_shp& point,
					   unsigned int size,
					   Color col)
	{
		aux_constructor(text, point.get_abscissa(), point.get_ordinate(), size,
						0, 3 + point.get_radius() + float(size) / 2, col);
	}

	Text_shp::Text_shp(const std::string& text,
					   const Segment_shp& segment,
					   unsigned int size,
					   Color col)
	{
		Coordinate x = (segment.get_origin_x() +
						segment.get_destination_x()) / 2;
		Coordinate y = (segment.get_origin_y() +
						segment.get_destination_y()) / 2;
		aux_constructor(text, x, y, size,
						0, 0, col);
	}

	Text_shp::Text_shp(const std::string& text,
					   const Vector_shp& vector,
					   unsigned int size,
					   Color col)
	{
		Coordinate x = (vector.get_origin_x() + vector.get_destination_x()) / 2;
		Coordinate y = (vector.get_origin_y() + vector.get_destination_y()) / 2;
		aux_constructor(text, x, y, size,
						0, 0, col);
	}

	std::string Text_shp::get_content() const
	{ return content; }

	Coordinate Text_shp::get_abscissa() const
	{ return point.abscissa; }

	Coordinate Text_shp::get_ordinate() const
	{ return point.ordinate; }

	unsigned Text_shp::get_size() const
	{ return size; }

	float Text_shp::get_offset_x() const
	{ return offset_x; }

	float Text_shp::get_offset_y() const
	{ return offset_y; }

	Color Text_shp::get_color() const
	{ return color; }

	void Text_shp::write(std::ostream& os) const
	{
		os << TEXT_NAME << " \""
		   << content << "\" "
		   << point.abscissa << " "
		   << point.ordinate << " "
		   << size << " "
		   << offset_x << " "
		   << offset_y << " "
		   << color;
	}

	void Text_shp::aux_constructor(const std::string& text,
								   const Coordinate& x,
								   const Coordinate& y,
								   unsigned char_size,
								   float off_x,
								   float off_y,
								   Color col)
	{
		content = std::string(text);
		point = Point_obj(x, y);
		size = char_size;
		offset_x = off_x;
		offset_y = off_y;
		color = col;

		bounding_box = Bounding_box(point);
	}

	std::ostream& operator<<(std::ostream& os,
							 const Text_shp& text)
	{
		text.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Text_shp& text)
	{
		text.content.clear();
		std::string tmp;
		is.get();
		auto c = is.get();
		do
		{
			text.content.push_back(c);
			c = is.get();
		} while (c != '"');

		is >> text.point.abscissa
		   >> text.point.ordinate
		   >> text.size
		   >> text.offset_x
		   >> text.offset_y
		   >> text.color;

		return is;
	}
}