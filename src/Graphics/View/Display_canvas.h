#pragma once

#include "Canvas.h"
#include "Graphics/Model/Animation.h"


namespace graphics
{
	// +-----------------------------------------------------------------------+
	// |                             DECLARATIONS                              |
	// +-----------------------------------------------------------------------+

	/*!
	 * The Display_canvas class handles the display of a Slide_show
	 */
	class Display_canvas : public Canvas
	{
	private:
		unsigned nb_slides = 0;
		unsigned slide_index = 0;

	public:
		Display_canvas() = default;
		~Display_canvas() = default;

		void display_figure(Figure& figure);
		void run_animation(Animation& animation);

	private:
		void handle_events();
		void next_slide();
		void prev_slide();
		void key_pressed_event(const sf::Event& event);
	};


	// +-----------------------------------------------------------------------+
	// |                              DEFINITIONS                              |
	// +-----------------------------------------------------------------------+

	void Display_canvas::display_figure(Figure& figure)
	{
		figure.make_bounding_box();
		bounding_box = figure.get_bounding_box();
		open();
		setup_view();
		while (window.isOpen())
		{
			handle_events();
			draw_figure(figure);
			window.display();
		}
	}

	void Display_canvas::run_animation(Animation& animation)
	{
		animation.get_ith_frame(0).make_bounding_box();
		bounding_box = animation.get_ith_frame(0).get_bounding_box();
		nb_slides = animation.nb_frames();
		open();
		setup_view();
		while (window.isOpen())
		{
			handle_events();
			draw_figure(animation.get_ith_frame(slide_index));
			window.display();
		}
	}

	void Display_canvas::next_slide()
	{
		if (slide_index < nb_slides - 1)
		{ slide_index++; }
	}

	void Display_canvas::prev_slide()
	{
		if (slide_index > 0)
		{ slide_index--; }
	}
}