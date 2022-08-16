#pragma once

#include "Canvas.h"
#include "graphics/Model/Animation.h"


namespace graphics
{
	/*!
	 * The Display_canvas class handles the display of an Animation
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
}