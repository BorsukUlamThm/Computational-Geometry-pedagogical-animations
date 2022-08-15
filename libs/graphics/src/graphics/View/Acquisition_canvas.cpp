#include "graphics/View/Acquisition_canvas.h"


namespace graphics
{
	void Acquisition_canvas::add_point_acquisition(unsigned nb_points,
												   Color col,
												   float rad)
	{
		auto point_acq = std::make_shared<Point_acq>(nb_points,
													 col,
													 rad);
		buffer.push_back(point_acq);
	}

	void Acquisition_canvas::add_segment_acquisition(unsigned nb_segments,
													 Color line_col,
													 Color endpoints_col)
	{
		auto segment_acq = std::make_shared<Segment_acq>(nb_segments,
														 line_col,
														 endpoints_col);
		buffer.push_back(segment_acq);
	}

	Acquisitions Acquisition_canvas::acquire_buffer()
	{
		config.margin = 0;
		open();
		set_next_state();
		while (window.isOpen())
		{
			handle_events();
			draw_figure(current_shapes);
			window.display();
		}

		Acquisitions acquisitions;
		std::swap(buffer, acquisitions);
		return acquisitions;
	}

	void Acquisition_canvas::setup_bounding_box()
	{
		if (current_shapes.is_empty())
		{
			graphics::Point_shp p(0, 0);
			graphics::Point_shp q(Coordinate(config.width),
								  Coordinate(config.height));

			bounding_box.clear();
			bounding_box.extend(p.get_bounding_box());
			bounding_box.extend(q.get_bounding_box());
		}
		else
		{
			bounding_box = Bounding_box(current_shapes.get_bounding_box());
		}
	}

	void Acquisition_canvas::set_next_state()
	{
		if (index < buffer.size() &&
			nb_acquired_shapes == buffer[index]->get_nb_acquisitions())
		{
			nb_acquired_shapes = 0;
			index++;
		}
		if (index >= buffer.size())
		{
			state = END_ACQ;
			return;
		}

		state = buffer[index]->starting_state();
	}

	void Acquisition_canvas::acquire_point(Coordinate& x,
										   Coordinate& y)
	{
		float ratio_x = mouse_x / float(config.width);
		float ratio_y = mouse_y / float(config.height);

		float view_size_x = view.getSize().x;
		float view_size_y = view.getSize().y;
		float x_min = view.getCenter().x - view.getSize().x / 2;
		float y_min = view.getCenter().y - view.getSize().y / 2;

		x = x_min + ratio_x * view_size_x;
		y = -y_min - ratio_y * view_size_y;
	}
}