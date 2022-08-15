#include "Graphics/View/Canvas.h"


namespace graphics
{
	std::string Canvas::get_title() const
	{ return window_title; }

	sf::Color Canvas::get_color(Color col) const
	{ return config.get_color(col); }

	sf::Color Canvas::get_background_color() const
	{ return config.colors[BACKGROUND_COLOR]; }

	sf::Color Canvas::get_default_plot_color() const
	{ return config.colors[DEFAULT_SHAPE_COLOR]; }

	sf::Font Canvas::get_font() const
	{ return config.font; }

	unsigned Canvas::get_width() const
	{ return config.width; }

	unsigned Canvas::get_height() const
	{ return config.height; }

	unsigned Canvas::get_margin() const
	{ return config.margin; }

	void Canvas::set_title(const std::string& new_title)
	{ window_title = new_title; }

	void Canvas::set_color(Color col, const sf::Color& new_col)
	{ config.colors[col] = new_col; }

	void Canvas::set_background_color(const sf::Color& new_color)
	{ config.colors[BACKGROUND_COLOR] = new_color; }

	void Canvas::set_default_plot_color(const sf::Color& new_color)
	{ config.colors[DEFAULT_SHAPE_COLOR] = new_color; }

	void Canvas::set_font(const sf::Font& new_font)
	{ config.font = new_font; }

	void Canvas::set_width(unsigned& new_width)
	{ config.width = new_width; }

	void Canvas::set_height(unsigned& new_height)
	{ config.height = new_height; }

	void Canvas::set_margin(unsigned& new_margin)
	{ config.margin = new_margin; }

	void Canvas::open()
	{
		window.clear(config.colors[BACKGROUND_COLOR]);
		if (window.isOpen())
		{ return; }

		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;

		if (config.width == -1 || config.height == -1)
		{
			window.create(sf::VideoMode::getDesktopMode(),
						  window_title,
						  sf::Style::Default, settings);
		}
		else
		{
			window.create(sf::VideoMode(config.width, config.height),
						  window_title,
						  sf::Style::Default, settings);
		}
	}

	void Canvas::setup_view()
	{
		Coordinate x_min = bounding_box.get_min_abscissa();
		Coordinate x_max = bounding_box.get_max_abscissa();
		Coordinate y_min = -bounding_box.get_max_ordinate();
		Coordinate y_max = -bounding_box.get_min_ordinate();

		if (x_min == x_max && y_min == y_max)
		{
			x_min -= 1;
			x_max += 1;
			y_min -= 1;
			y_max += 1;
		}

		float window_format = float(config.width) / float(config.height);
		float figure_format = (x_max - x_min) / (y_max - y_min);
		float x_length = (x_max - x_min) / zoom;
		float y_length = (y_max - y_min) / zoom;

		if (window_format < figure_format)
		{
			float margin_offset = 2 * config.margin / float(config.width);
			margin_offset /= (1 - margin_offset);
			margin_offset *= x_length;
			view.setSize(margin_offset + x_length,
						 margin_offset + x_length / window_format);
		}
		else
		{
			float margin_offset = 2 * config.margin / float(config.height);
			margin_offset /= (1 - margin_offset);
			margin_offset *= x_length;
			view.setSize(margin_offset + y_length * window_format,
						 margin_offset + y_length);
		}

		float ratio = view.getSize().x / float(config.width);
		view.setCenter(-ratio * (offset_x + hold_offset_x)
					   + (x_min + x_max) / 2,
					   -ratio * (offset_y + hold_offset_y)
					   + (y_min + y_max) / 2);

		window.setView(view);
	}

	void Canvas::reset_zoom_and_offsets()
	{
		offset_x = 0;
		offset_y = 0;
		hold_x = 0;
		hold_y = 0;
		hold_offset_y = 0;
		hold_offset_x = 0;
		zoom = 1;
	}
}