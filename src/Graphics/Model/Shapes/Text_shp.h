#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Vector_shp.h"

namespace gr
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * Contains the needed information to draw a line\n
	 * \n
	 * -> content of the text\n
	 * -> coordinate where the text should be displayed\n
	 * -> font size, in pixel\n
	 * -> vertical and horizontal offsets, in pixels\n
	 * -> color\n
	 */
	class Text_shp : public Shape
	{
	private:
		std::string content{};
		Coordinate abscissa{};
		Coordinate ordinate{};
		unsigned size = 16;
		float offset_x = 0;
		float offset_y = 0;
		Color color = DEFAULT_PLOT_COLOR;

	public:
		// standard constructors
		Text_shp() = default;
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

		Coordinate get_min_abscissa() const override;
		Coordinate get_max_abscissa() const override;
		Coordinate get_min_ordinate() const override;
		Coordinate get_max_ordinate() const override;

		void draw(Canvas& canvas) const override;

		friend std::istream& operator>>(std::istream& is,
										Text_shp& text);

	private:
		void aux_constructor(const std::string& text,
							 const Coordinate& x,
							 const Coordinate& y,
							 unsigned size,
							 float off_x,
							 float off_y,
							 Color col);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

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

	Text_shp::Text_shp(const Text_shp& other)
	{
		content = std::string(other.content);
		abscissa = Coordinate(other.abscissa);
		ordinate = Coordinate(other.ordinate);
		size = other.size;
		offset_x = other.offset_x;
		offset_y = other.offset_y;
		color = other.color;
	}

	std::string Text_shp::get_content() const
	{
		return content;
	}

	Coordinate Text_shp::get_abscissa() const
	{
		return abscissa;
	}

	Coordinate Text_shp::get_ordinate() const
	{
		return ordinate;
	}

	unsigned Text_shp::get_size() const
	{
		return size;
	}

	float Text_shp::get_offset_x() const
	{
		return offset_x;
	}

	float Text_shp::get_offset_y() const
	{
		return offset_y;
	}

	Color Text_shp::get_color() const
	{
		return color;
	}

	Coordinate Text_shp::get_min_abscissa() const
	{
		return abscissa;
	}

	Coordinate Text_shp::get_max_abscissa() const
	{
		return abscissa;
	}

	Coordinate Text_shp::get_min_ordinate() const
	{
		return ordinate;
	}

	Coordinate Text_shp::get_max_ordinate() const
	{
		return ordinate;
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
		if(text.content[text.content.size() - 1] == '\"')
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