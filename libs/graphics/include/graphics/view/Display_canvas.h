#pragma once

#include "Canvas.h"
#include "graphics/model/Animation.h"


namespace graphics
{
	enum State_dsp
	{
		RUN,
		PAUSE
	};

	/*!
	 * The Display_canvas class handles the display of an Animation
	 */
	class Display_canvas : public Canvas
	{
	private:
		unsigned nb_frames = 0;
		unsigned frame_index = 0;
		State_dsp state = PAUSE;
		unsigned frame_time = 64;

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

		float display_frame_index();
		void display_speed(float offset);
		void display_help();
	};
}