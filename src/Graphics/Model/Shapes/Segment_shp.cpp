#include "Graphics/Model/Shapes/Segment_shp.h"


namespace graphics
{
	Segment_shp::Segment_shp()
	{
		bounding_box = Bounding_box(segment);
	}

	Segment_shp::Segment_shp(const Coordinate& ogn_x,
							 const Coordinate& ogn_y,
							 const Coordinate& dst_x,
							 const Coordinate& dst_y,
							 Color line_col,
							 Color end_points_col)
	{
		segment = Segment_obj(ogn_x, ogn_y, dst_x, dst_y);
		line_color = line_col;
		endpoints_color = end_points_col;
		bounding_box = Bounding_box(segment);
	}

	Segment_shp::Segment_shp(const Segment_shp& other) : Shape(other)
	{
		segment = Segment_obj(other.segment);
		line_color = other.line_color;
		endpoints_color = other.endpoints_color;
	}

	Segment_shp::Segment_shp(const Point_obj& ogn,
							 const Point_obj& dst,
							 Color line_col,
							 Color endpoints_col)
	{
		segment = Segment_obj(ogn, dst);
		line_color = line_col;
		endpoints_color = endpoints_col;
		bounding_box = Bounding_box(segment);
	}

	Coordinate Segment_shp::get_origin_x() const
	{ return segment.origin_x; }

	Coordinate Segment_shp::get_origin_y() const
	{ return segment.origin_y; }

	Coordinate Segment_shp::get_destination_x() const
	{ return segment.destination_x; }

	Coordinate Segment_shp::get_destination_y() const
	{ return segment.destination_y; }

	Color Segment_shp::get_line_color() const
	{ return line_color; }

	Color Segment_shp::get_endpoints_color() const
	{ return line_color; }

	void Segment_shp::write(std::ostream& os) const
	{
		os << SEGMENT_NAME << " "
		   << segment.origin_x << " "
		   << segment.origin_y << " "
		   << segment.destination_x << " "
		   << segment.destination_y << " "
		   << line_color << " "
		   << endpoints_color;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Segment_shp& segment)
	{
		segment.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Segment_shp& segment)
	{
		is >> segment.segment.origin_x
		   >> segment.segment.origin_y
		   >> segment.segment.destination_x
		   >> segment.segment.destination_y
		   >> segment.line_color
		   >> segment.endpoints_color;
		return is;
	}
}