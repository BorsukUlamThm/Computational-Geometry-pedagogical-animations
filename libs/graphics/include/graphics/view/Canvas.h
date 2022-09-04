#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "graphics/model/Figure.h"


namespace graphics
{
	/*!
	 * The Canvas class will handle all the drawing of Figure\n
	 */
	class Canvas
	{
	protected:
		sf::RenderWindow window;
		Bounding_box bounding_box;
		sf::View view;

		std::string window_title = "CGPA";
		Config config;

		float zoom = 1;
		float zoom_factor = 1.1;
		float offset_x = 0;
		float offset_y = 0;
		float hold_x = 0;
		float hold_y = 0;
		float hold_offset_x = 0;
		float hold_offset_y = 0;

		enum Mouse_button
		{
			NONE,
			LEFT,
			RIGHT,
			MIDDLE,
			PREV,
			NEXT
		};
		Mouse_button mouse_button = NONE;
		float mouse_x = 0;
		float mouse_y = 0;

	public:
		Canvas() = default;
		~Canvas() = default;

		std::string get_title() const;
		sf::Color get_color(Color col) const;
		sf::Color get_background_color() const;
		sf::Color get_default_plot_color() const;
		sf::Font get_font() const;
		unsigned get_width() const;
		unsigned get_height() const;
		unsigned get_margin() const;

		void set_title(const std::string& new_title);
		void set_color(Color col, const sf::Color& new_col);
		void set_background_color(const sf::Color& new_color);
		void set_default_plot_color(const sf::Color& new_color);
		void set_font(const sf::Font& new_font);
		void set_width(unsigned& new_width);
		void set_height(unsigned& new_height);
		void set_margin(unsigned& new_margin);

		void draw_figure(const Figure& figure);

	protected:
		void open();
		void setup_view();
		void reset_zoom_and_offsets();

		void mouse_wheel_scrolled_event(const sf::Event& event);
		void mouse_button_pressed_event(const sf::Event& event);
		void mouse_button_released_event(const sf::Event& event);
		void mouse_moved_event(const sf::Event& event);

		friend void Point_shp::draw(Canvas& canvas) const;
		friend void Segment_shp::draw(Canvas& canvas) const;
		friend void Line_shp::draw(Canvas& canvas) const;
		friend void Polygon_shp::draw(Canvas& canvas) const;
		friend void Circle_shp::draw(Canvas& canvas) const;
		friend void Vector_shp::draw(Canvas& canvas) const;
		friend void Text_shp::draw(Canvas& canvas) const;
	};
}