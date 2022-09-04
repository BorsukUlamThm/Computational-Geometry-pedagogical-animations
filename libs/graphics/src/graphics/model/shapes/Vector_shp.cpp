#include "graphics/model/shapes/Vector_shp.h"


namespace graphics
{
	Vector_shp::Vector_shp()
	{
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Point_obj& ogn,
						   const Point_obj& dst,
						   Color col)
	{
		vector = Segment_obj(ogn, dst);
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Vector_shp& other) : Shape(other)
	{
		vector = Segment_obj(other.vector);
		color = other.color;
	}

	Vector_shp::Vector_shp(const Coordinate& ogn_x,
						   const Coordinate& ogn_y,
						   const Coordinate& dst_x,
						   const Coordinate& dst_y,
						   Color col)
	{
		vector = Segment_obj(ogn_x, ogn_y, dst_x, dst_y);
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Vector_shp::Vector_shp(const Segment_obj& segment,
						   Color col)
	{
		vector = Segment_obj(segment);
		color = col;
		bounding_box = Bounding_box(vector);
	}

	Point_obj Vector_shp::get_origin() const
	{ return vector.origin; }

	Point_obj Vector_shp::get_destination() const
	{ return vector.destination; }

	Color Vector_shp::get_color() const
	{ return color; }

	void Vector_shp::write(std::ostream& os) const
	{
		os << VECTOR_NAME << " "
		   << vector << " "
		   << color;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Vector_shp& vector)
	{
		vector.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Vector_shp& vector)
	{
		is >> vector.vector
		   >> vector.color;
		return is;
	}
}