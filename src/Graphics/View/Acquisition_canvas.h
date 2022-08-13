#pragma once

#include "Graphics/Model/Acquisitions/Point_acq.h"
#include "Graphics/Model/Acquisitions/Segment_acq.h"
#include "Canvas.h"


namespace graphics
{
	typedef std::shared_ptr<Acquisition> Acquisition_ptr;
	typedef std::vector<Acquisition_ptr> Acquisitions;

	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * The Acquisition_canvas class allows to acquire shapes in order to perform
	 * algorithms on them\n
	 */
	class Acquisition_canvas : public Canvas
	{
	private:
		Acquisitions buffer;
		unsigned index = 0;
		unsigned nb_acquired_shapes = 0;
		Figure current_shapes;
		State state = BEGIN_ACQ;

	public:
		Acquisition_canvas() = default;
		~Acquisition_canvas() = default;

		void add_point_acquisition(unsigned nb_points = -1,
								   Color col = DEFAULT_SHAPE_COLOR,
								   float rad = 3);
		void add_segment_acquisition(unsigned nb_segments = -1,
									 Color line_col = DEFAULT_SHAPE_COLOR,
									 Color endpoints_col = DEFAULT_SHAPE_COLOR);

		Acquisitions acquire_buffer();

	private:
		void setup_bounding_box();
		void set_next_state();
		void acquire_point(Coordinate& x,
						   Coordinate& y);

		void handle_events();
		void handle_point(Coordinate x,
						  Coordinate y);
		void key_pressed_event(const sf::Event& event);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

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