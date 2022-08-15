#include "graphics/View/Acquisition_canvas.h"


namespace graphics
{
	void Acquisition_canvas::handle_events()
	{
		sf::Event event {};
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::Resized:
					config.width = event.size.width;
					config.height = event.size.height;
					setup_bounding_box();
					setup_view();
					break;

				case sf::Event::MouseButtonPressed:
					mouse_button_pressed_event(event);
					break;

				case sf::Event::MouseWheelScrolled:
					mouse_wheel_scrolled_event(event);
					break;

				case sf::Event::MouseButtonReleased:
					mouse_button_released_event(event);
					break;

				case sf::Event::MouseMoved:
					mouse_moved_event(event);
					break;

				case sf::Event::KeyPressed:
					key_pressed_event(event);
					break;

				default:
					break;
			}
		}
	}

	void Acquisition_canvas::handle_point(Coordinate x,
										  Coordinate y)
	{
		if (index >= buffer.size())
		{ return; }

		switch (state)
		{
			case BEGIN_ACQ:
			case END_ACQ:
				break;

			case POINT_ACQ1:
				current_shapes.add_point
						(x, y,
						 std::dynamic_pointer_cast<Point_acq>
								 (buffer[index])->get_color(),
						 std::dynamic_pointer_cast<Point_acq>
								 (buffer[index])->get_radius());

				std::dynamic_pointer_cast<Point_acq>
						(buffer[index])->add_point(x, y);

				nb_acquired_shapes++;
				set_next_state();
				break;

			case SEGMENT_ACQ1:
				current_shapes.add_point
						(x, y,
						 std::dynamic_pointer_cast<Segment_acq>
								 (buffer[index])->get_endpoints_color());

				std::dynamic_pointer_cast<Segment_acq>
						(buffer[index])->add_origin(x, y);

				state = SEGMENT_ACQ2;
				break;

			case SEGMENT_ACQ2:
				Point_shp p = *(std::dynamic_pointer_cast<Point_shp>
						(current_shapes.get_last_shape()));

				current_shapes.erase_last_shape();
				current_shapes.add_segment
						(p.get_abscissa(), p.get_ordinate(),
						 x, y,
						 std::dynamic_pointer_cast<Segment_acq>
								 (buffer[index])->get_line_color(),
						 std::dynamic_pointer_cast<Segment_acq>
								 (buffer[index])->get_endpoints_color());

				std::dynamic_pointer_cast<Segment_acq>
						(buffer[index])->add_destination(x, y);

				state = SEGMENT_ACQ1;
				nb_acquired_shapes++;
				set_next_state();
				break;
		}
	}

	void Acquisition_canvas::key_pressed_event(const sf::Event& event)
	{
		switch (event.key.code)
		{
			case sf::Keyboard::Enter:
				if (index >= buffer.size())
				{ break; }
				if (buffer[index]->get_nb_acquisitions() < -1 &&
					buffer[index]->get_nb_acquisitions() > nb_acquired_shapes)
				{ break; }

				index++;
				nb_acquired_shapes = 0;
				set_next_state();
				break;

			case sf::Keyboard::Space:
				Coordinate x;
				Coordinate y;
				acquire_point(x, y);
				handle_point(x, y);
				break;

			case sf::Keyboard::Escape:
				window.clear();
				window.close();
				break;

			default:
				break;
		}
	}
}