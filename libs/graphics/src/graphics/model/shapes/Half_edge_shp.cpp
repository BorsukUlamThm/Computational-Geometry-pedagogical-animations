#include "graphics/model/shapes/Half_edge_shp.h"


namespace graphics
{
	Half_edge_shp::Half_edge_shp()
	{
		bounding_box = Bounding_box(arrow);
	}

	Half_edge_shp::Half_edge_shp(const Point_obj& ogn,
								 const Point_obj& dst,
								 Color arrow_col,
								 Color vertices_col)
	{
		arrow = Segment_obj(ogn, dst);
		arrow_color = arrow_col;
		vertices_color = vertices_col;
		bounding_box = Bounding_box(arrow);
	}

	Half_edge_shp::Half_edge_shp(const Half_edge_shp& other) :
			Shape(other)
	{
		arrow = Segment_obj(other.arrow);
		arrow_color = other.arrow_color;
		vertices_color = other.vertices_color;
	}

	Half_edge_shp::Half_edge_shp(const Coordinate& ogn_x,
								 const Coordinate& ogn_y,
								 const Coordinate& dst_x,
								 const Coordinate& dst_y,
								 Color arrow_col,
								 Color vertices_col)
	{
		arrow = Segment_obj(ogn_x, ogn_y, dst_x, dst_y);
		arrow_color = arrow_col;
		vertices_color = vertices_col;
		bounding_box = Bounding_box(arrow);
	}

	Point_obj Half_edge_shp::get_origin() const
	{ return arrow.origin; }

	Point_obj Half_edge_shp::get_destination() const
	{ return arrow.destination; }

	Color Half_edge_shp::get_arrow_color() const
	{ return arrow_color; }

	Color Half_edge_shp::get_vertices_color() const
	{ return vertices_color; }

	void Half_edge_shp::write(std::ostream& os) const
	{
		os << HALF_EDGE_NAME << " "
		   << arrow << " "
		   << arrow_color << " "
		   << vertices_color;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Half_edge_shp& double_edge)
	{
		double_edge.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Half_edge_shp& double_edge)
	{
		is >> double_edge.arrow
		   >> double_edge.arrow_color
		   >> double_edge.vertices_color;
		return is;
	}
}