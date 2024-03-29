#include "graphics/view/Animation_canvas.h"
#include <chrono>
#include <thread>
#include <cmath>
#include <iomanip>
#include <sstream>


namespace graphics
{
	void Animation_canvas::speed_up()
	{
		frame_time = (frame_time > 1 ? frame_time / 2 : frame_time);
	}

	void Animation_canvas::slow_down()
	{
		frame_time = (frame_time < unsigned(-1) / 2 ?
					  frame_time * 2 : frame_time);
	}

	void Animation_canvas::display_figure(Figure& figure)
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

	void Animation_canvas::run_animation(Animation& animation)
	{
		for (unsigned i = 0; i < animation.nb_frames(); ++i)
		{ animation.get_ith_frame(i).make_bounding_box(); }
		bounding_box = animation.get_ith_frame(0).get_bounding_box();
		for (unsigned i = 0; i < animation.nb_frames(); ++i)
		{ bounding_box.extend(animation.get_ith_frame(i).get_bounding_box()); }

		nb_frames = animation.nb_frames();
		reset_zoom_and_offsets();

		open();
		setup_view();
		while (window.isOpen())
		{
			handle_events();
			draw_figure(animation.get_ith_frame(frame_index));
			float offset = display_frame_index();
			display_speed(offset);
			window.display();

			if (state == RUN)
			{
				next_slide();
				std::this_thread::sleep_for(
						std::chrono::milliseconds(frame_time));
			}
		}
	}

	void Animation_canvas::next_slide()
	{
		if (frame_index < nb_frames - 1)
		{ frame_index++; }
	}

	void Animation_canvas::prev_slide()
	{
		if (frame_index > 0)
		{ frame_index--; }
	}

	float Animation_canvas::display_frame_index()
	{
		sf::Text text;
		text.setFont(config.font);
		text.setCharacterSize(16);

		std::string str = "frame ";
		str += std::to_string(frame_index + 1);
		str += " / ";
		str += std::to_string(nb_frames);
		text.setString(str);

		float ratio = view.getSize().x / float(config.width);
		text.setScale(ratio, ratio);

		text.setFillColor(get_color(DEFAULT_SHAPE_COLOR));
		text.setOutlineColor(config.colors[BACKGROUND_COLOR]);
		text.setOutlineThickness(2);

		float offset = 150;
		text.move(view.getCenter());
		text.move(view.getSize().x / 2 - offset * ratio,
				  view.getSize().y / 2 - config.margin * ratio / 2);
		window.draw(text);

		return offset;
	}

	void Animation_canvas::display_speed(float offset)
	{
		sf::Text text;
		text.setFont(config.font);
		text.setCharacterSize(16);

		double factor = std::pow(2, 6 - std::log2(frame_time));
		std::string str = "speed x";
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << factor;
		str += stream.str();
		while (str[str.size() - 1] == '0')
		{
			str = str.substr(0, str.size() - 1);
		}
		if (str[str.size() - 1] == '.')
		{
			str = str.substr(0, str.size() - 1);
		}
		text.setString(str);

		float ratio = view.getSize().x / float(config.width);
		text.setScale(ratio, ratio);

		text.setFillColor(get_color(DEFAULT_SHAPE_COLOR));
		text.setOutlineColor(config.colors[BACKGROUND_COLOR]);
		text.setOutlineThickness(2);

		offset += 100;
		text.move(view.getCenter());
		text.move(view.getSize().x / 2 - offset * ratio,
				  view.getSize().y / 2 - config.margin * ratio / 2);
		window.draw(text);
	}
}