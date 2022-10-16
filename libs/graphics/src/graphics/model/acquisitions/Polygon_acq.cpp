#include "graphics/model/acquisitions/Polygon_acq.h"


namespace graphics
{
	Polygon_acq::Polygon_acq(unsigned int nb_polygons,
							 graphics::Color edges_col,
							 graphics::Color vertices_col)
	{
		name = "polygon acquisition";
		nb_acquisitions = nb_polygons;
		edges_color = edges_col;
		vertices_color = vertices_col;
	}

	State_acq Polygon_acq::starting_state() const
	{ return POLYGON_ACQ1; }

	Color Polygon_acq::get_edges_color() const
	{ return edges_color; }

	Color Polygon_acq::get_vertices_color() const
	{ return vertices_color; }

	Coordinate Polygon_acq::get_first_vertex_x() const
	{ return buffer[0].abscissa; }

	Coordinate Polygon_acq::get_first_vertex_y() const
	{ return buffer[0].ordinate; }

	Coordinate Polygon_acq::get_last_vertex_x() const
	{ return buffer[buffer.size() - 1].abscissa; }

	Coordinate Polygon_acq::get_last_vertex_y() const
	{ return buffer[buffer.size() - 1].ordinate; }

	void Polygon_acq::add_vertex(const Coordinate& x,
								 const Coordinate& y)
	{ buffer.emplace_back(x, y); }

	void Polygon_acq::add_buffer()
	{
//		Polygon_obj copy;
//		for (auto& point : buffer)
//		{ copy.emplace_back(point.abscissa, point.ordinate); }

		Geometric_object_ptr polygon =
				std::make_shared<Polygon_obj>(buffer);
		acquired_shapes.emplace_back(polygon);

		buffer.clear();
	}
}