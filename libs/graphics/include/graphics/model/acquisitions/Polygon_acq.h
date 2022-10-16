#pragma once

#include "Acquisition.h"


namespace graphics
{
	class Polygon_acq : public Acquisition
	{
	private:
		Color edges_color = DEFAULT_SHAPE_COLOR;
		Color vertices_color = DEFAULT_SHAPE_COLOR;

		Polygon_obj buffer {};

	public:
		explicit Polygon_acq(unsigned nb_polygons = -1,
							 Color edges_col = DEFAULT_SHAPE_COLOR,
							 Color vertices_col = DEFAULT_SHAPE_COLOR);

		State_acq starting_state() const override;
		Color get_edges_color() const;
		Color get_vertices_color() const;

		Coordinate get_first_vertex_x() const;
		Coordinate get_first_vertex_y() const;
		Coordinate get_last_vertex_x() const;
		Coordinate get_last_vertex_y() const;

		void add_vertex(const Coordinate& x,
						const Coordinate& y);
		void add_buffer();
	};
}