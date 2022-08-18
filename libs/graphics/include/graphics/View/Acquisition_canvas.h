#pragma once

#include "graphics/Model/Acquisitions/Acquisition.h"
#include "Canvas.h"


namespace graphics
{
	typedef std::shared_ptr<Acquisition> Acquisition_ptr;
	typedef std::vector<Acquisition_ptr> Acquisitions;

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

		void display_help();
	};
}