#include "graphics/model/shapes/Text_shp.h"


namespace graphics
{
	Text_shp::Text_shp()
	{
		bounding_box = Bounding_box(point);
	}

	Text_shp::Text_shp(const std::string& text,
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

	Text_shp::Text_shp(const Text_shp& other) : Shape(other)
	{
		content = std::string(other.content);
		point = Point_obj(other.point);
		size = other.size;
		offset_x = other.offset_x;
		offset_y = other.offset_y;
		color = other.color;
	}

	Text_shp::Text_shp(const std::string& text,
					   const Point_obj& point,
					   unsigned int size,
					   const Color col) :
			Text_shp(text, point.abscissa, point.ordinate,
					 size, 0, 0, col)
	{}

	Text_shp::Text_shp(const std::string& text,
					   const Point_shp& point,
					   unsigned int size,
					   Color col) :
			Text_shp(text, point.get_abscissa(), point.get_ordinate(),
					 size, 0, 3 + point.get_radius() + float(size) / 2, col)
	{}

	Text_shp::Text_shp(const std::string& text,
					   const Segment_obj& segment,
					   unsigned int size,
					   Color col) :
			Text_shp(text,
					 (segment.origin.abscissa +
					  segment.destination.abscissa) / 2,
					 (segment.origin.ordinate +
					  segment.destination.ordinate) / 2,
					 size, 0, 0, col)
	{}

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
		   << point << " "
		   << size << " "
		   << offset_x << " "
		   << offset_y << " "
		   << color;
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
		std::string word;
		do
		{
			is >> word;
			text.content += word + " ";
		} while (word[word.size() - 1] != '"');
		text.content = text.content.substr(1, text.content.size() - 3);

		is >> text.point
		   >> text.size
		   >> text.offset_x
		   >> text.offset_y
		   >> text.color;

		return is;
	}

}