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
	 *          const Color col = DEFAULT_PLOT_COLOR)
	 * ```
	 * which was already designed for this usecase, but it gives you an idea\n
	 */
	class Text_shp : public Shape
	{
	private:
		std::string content {};
		Coordinate abscissa {};
		Coordinate ordinate {};
		unsigned size = 16;
		float offset_x = 0;
		float offset_y = 0;
		Color color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Text_shp();
		Text_shp(const std::string& text,
				 const Coordinate& x,
				 const Coordinate& y,
				 unsigned size = 16,
				 float off_x = 0,
				 float off_y = 0,
				 const Color col = DEFAULT_PLOT_COLOR);
		Text_shp(const Text_shp& other);

		// other constructors
		/*!
		 * Constructs a text that will be drawn
		 * just above the given point
		 */
		Text_shp(const std::string& text,
				 const Point_shp& point,
				 unsigned size = 16,
				 const Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs a text that will be drawn
		 * in the middle of the given segment
		 */
		Text_shp(const std::string& text,
				 const Segment_shp& segment,
				 unsigned size = 16,
				 const Color col = DEFAULT_PLOT_COLOR);
		/*!
		 * Constructs a text that will be drawn
		 * in the middle of the given vector
		 */
		Text_shp(const std::string& text,
				 const Vector_shp& vector,
				 unsigned size = 16,
				 const Color col = DEFAULT_PLOT_COLOR);

		~Text_shp() = default;

		std::string get_content() const;
		Coordinate get_abscissa() const;
		Coordinate get_ordinate() const;
		unsigned get_size() const;
		float get_offset_x() const;
		float get_offset_y() const;
		Color get_color() const;

		void draw(Canvas& canvas) const override;

	private:
		void make_bounding_box();
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
		make_bounding_box();
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
		abscissa = Coordinate(other.abscissa);
		ordinate = Coordinate(other.ordinate);
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
		Coordinate x = (segment.get_origin().get_abscissa() +
						segment.get_destination().get_abscissa()) / 2;
		Coordinate y = (segment.get_origin().get_ordinate() +
						segment.get_destination().get_ordinate()) / 2;
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
	{ return abscissa; }

	Coordinate Text_shp::get_ordinate() const
	{ return ordinate; }

	unsigned Text_shp::get_size() const
	{ return size; }

	float Text_shp::get_offset_x() const
	{ return offset_x; }

	float Text_shp::get_offset_y() const
	{ return offset_y; }

	Color Text_shp::get_color() const
	{ return color; }

	void Text_shp::make_bounding_box()
	{
		bounding_box = Bounding_box(abscissa, abscissa, ordinate, ordinate);
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
		abscissa = Coordinate(x);
		ordinate = Coordinate(y);
		size = char_size;
		offset_x = off_x;
		offset_y = off_y;
		color = col;

		make_bounding_box();
	}

	std::ostream& operator<<(std::ostream& os,
							 const Text_shp& text)
	{
		os << TEXT_NAME << " \""
		   << text.get_content() << "\" "
		   << text.get_abscissa() << " "
		   << text.get_ordinate() << " "
		   << text.get_size() << " "
		   << text.get_offset_x() << " "
		   << text.get_offset_y() << " "
		   << text.get_color();
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Text_shp& text)
	{
		text.content.clear();
		std::string tmp;
		is >> tmp;
		text.content = tmp.substr(1, tmp.size() - 1);
		if (text.content[text.content.size() - 1] == '\"')
		{
			text.content = text.content.substr(0, tmp.size() - 1);
		}
		else
		{
			is >> tmp;
			while (tmp[tmp.size() - 1] != '\"')
			{
				text.content += tmp;
				is >> tmp;
			}
			text.content += tmp.substr(0, tmp.size() - 1);
		}

		is >> text.abscissa
		   >> text.ordinate
		   >> text.size
		   >> text.offset_x
		   >> text.offset_y;

		return is;
	}
}