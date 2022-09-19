#pragma once

#include "Canvas.h"
#include "graphics/model/Animation.h"


namespace graphics
{
	enum State_anim
	{
		RUN,
		PAUSE
	};

	/*!
	 * The Display_canvas class handles the display of an Animation
	 */
	class Animation_canvas : public Canvas
	{
	private:
		unsigned nb_frames = 0;
		unsigned frame_index = 0;
		State_anim state = PAUSE;
		unsigned frame_time = 64;

	public:
		Animation_canvas() = default;
		~Animation_canvas() = default;

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