#pragma once

/** @cond */
#include <cmath>
/** @endcond */
#include "Canvas.h"


namespace graphics
{
	void Canvas::mouse_wheel_scrolled_event(const sf::Event& event)
	{
		float zoom_ratio = std::pow(zoom_factor, event.mouseWheelScroll.delta);
		zoom *= zoom_ratio;

		float zoom_center_x = float(config.width) / 2 + offset_x;
		float zoom_center_y = float(config.height) / 2 + offset_y;
		auto x = float(event.mouseWheelScroll.x);
		auto y = float(event.mouseWheelScroll.y);
		offset_x += (x - zoom_center_x) * (1 - zoom_ratio);
		offset_y += (y - zoom_center_y) * (1 - zoom_ratio);

		setup_view();
	}

	void Canvas::mouse_button_pressed_event(const sf::Event& event)
	{
		if (mouse_button != NONE)
		{ return; }

		switch (event.mouseButton.button)
		{
			case sf::Mouse::Left:
				mouse_button = LEFT;
				hold_x = float(event.mouseButton.x);
				hold_y = float(event.mouseButton.y);
				break;

			case sf::Mouse::Right:
				mouse_button = RIGHT;
				offset_x = 0;
				offset_y = 0;
				hold_x = 0;
				hold_y = 0;
				hold_offset_y = 0;
				hold_offset_x = 0;
				zoom = 1;
				break;

			case sf::Mouse::Middle:
				mouse_button = MIDDLE;
				break;

			case sf::Mouse::XButton1:
				mouse_button = PREV;
				break;

			case sf::Mouse::XButton2:
				mouse_button = NEXT;
				break;

			default:
				break;
		}
	}

	void Canvas::mouse_button_released_event(const sf::Event& event)
	{
		switch (mouse_button)
		{
			case LEFT:
				offset_x += hold_offset_x;
				offset_y += hold_offset_y;
				hold_offset_x = 0;
				hold_offset_y = 0;
				break;

			default:
				break;
		}
		mouse_button = NONE;
		setup_view();
	}

	void Canvas::mouse_moved_event(const sf::Event& event)
	{
		mouse_x = float(event.mouseMove.x);
		mouse_y = float(event.mouseMove.y);

		switch (mouse_button)
		{
			case LEFT:
				hold_offset_x = float(event.mouseMove.x) - hold_x;
				hold_offset_y = float(event.mouseMove.y) - hold_y;
				setup_view();
				break;

			default:
				break;
		}
	}
}