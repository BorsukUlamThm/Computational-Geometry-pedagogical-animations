#include "graphics/model/shapes/Double_edge_shp.h"


namespace graphics
{
	Double_edge_shp::Double_edge_shp()
	{
		bounding_box = Bounding_box(edge);
	}

	Double_edge_shp::Double_edge_shp(const Point_obj& ogn,
									 const Point_obj& dst,
									 Color arrow1_col,
									 Color arrow2_col,
									 Color vertices_col)
	{
		edge = Segment_obj(ogn, dst);
		arrow1_color = arrow1_col;
		arrow2_color = arrow2_col;
		vertices_color = vertices_col;
		bounding_box = Bounding_box(edge);
	}

	Double_edge_shp::Double_edge_shp(const Double_edge_shp& other) :
			Shape(other)
	{
		edge = Segment_obj(other.edge);
		arrow1_color = other.arrow1_color;
		arrow2_color = other.arrow2_color;
		vertices_color = other.vertices_color;
	}

	Double_edge_shp::Double_edge_shp(const Coordinate& ogn_x,
									 const Coordinate& ogn_y,
									 const Coordinate& dst_x,
									 const Coordinate& dst_y,
									 Color arrow1_col,
									 Color arrow2_col,
									 Color vertices_col)
	{
		edge = Segment_obj(ogn_x, ogn_y, dst_x, dst_y);
		arrow1_color = arrow1_col;
		arrow2_color = arrow2_col;
		vertices_color = vertices_col;
		bounding_box = Bounding_box(edge);
	}

	Point_obj Double_edge_shp::get_origin() const
	{ return edge.origin; }

	Point_obj Double_edge_shp::get_destination() const
	{ return edge.destination; }

	Color Double_edge_shp::get_arrows_color() const
	{ return arrow1_color; }

	Color Double_edge_shp::get_vertices_color() const
	{ return vertices_color; }

	void Double_edge_shp::write(std::ostream& os) const
	{
		os << DOUBLE_EDGE_NAME << " "
		   << edge << " "
		   << arrow1_color << " "
		   << arrow2_color << " "
		   << vertices_color;
	}

	std::ostream& operator<<(std::ostream& os,
							 const Double_edge_shp& double_edge)
	{
		double_edge.write(os);
		return os;
	}

	std::istream& operator>>(std::istream& is,
							 Double_edge_shp& double_edge)
	{
		is >> double_edge.edge
		   >> double_edge.arrow1_color
		   >> double_edge.arrow2_color
		   >> double_edge.vertices_color;
		return is;
	}
}