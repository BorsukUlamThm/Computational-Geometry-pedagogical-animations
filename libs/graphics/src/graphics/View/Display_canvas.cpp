#include "graphics/View/Display_canvas.h"


namespace graphics
{
	void Display_canvas::display_figure(Figure& figure)
	{
		figure.make_bounding_box();
		bounding_box = figure.get_bounding_box();
		reset_zoom_and_offsets();

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
		reset_zoom_and_offsets();

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