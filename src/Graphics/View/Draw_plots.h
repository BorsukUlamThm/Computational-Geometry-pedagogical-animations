#pragma once

/** @cond */
#include <cmath>
/** @endcond */
#include "Canvas.h"


namespace gr
{
	void Canvas::draw_figure(const Figure& figure)
	{
		window.clear(config.colors[BACKGROUND_COLOR]);
		for(unsigned i = 0; i < figure.nb_plots(); ++i)
		{
			switch(figure[i].type())
			{
				case POINT_PLT:
					draw_point(figure[i].point());
					break;
				case SEGMENT_PLT:
					draw_segment(figure[i].segment());
					break;
				case VECTOR_PLT:
					draw_vector(figure[i].vector());
					break;
				case POLYGON_PLT:
					draw_polygon(figure[i].polygon());
					break;
				case CIRCLE_PLT:
					draw_circle(figure[i].circle());
					break;
				case LINE_PLT:
					draw_line(figure[i].line());
					break;
				case TEXT_PLT:
					draw_text(figure[i].text());
					break;
			}
		}
	}

	void Canvas::draw_point(const Point_plot& point)
	{
		float radius = point.get_radius() * view.getSize().x / float(config.width);
		sf::CircleShape shape(radius);
		shape.move(point.get_abscissa() - radius,
				   -point.get_ordinate() - radius);
		shape.setFillColor(get_color(point.get_color()));
		window.draw(shape);
	}

	void Canvas::draw_segment(const Segment_plot& segment)
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(segment.get_origin().get_abscissa(),
										 -segment.get_origin().get_ordinate());
		shape[1].position = sf::Vector2f(segment.get_destination().get_abscissa(),
										 -segment.get_destination().get_ordinate());
		shape[0].color = get_color(segment.get_line_color());
		shape[1].color = get_color(segment.get_line_color());
		window.draw(shape);
		draw_point(segment.get_origin());
		draw_point(segment.get_destination());
	}

	void Canvas::draw_vector(const Vector_plot& vector)
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(vector.get_origin_x(),
										 -vector.get_origin_y());
		shape[1].position = sf::Vector2f(vector.get_destination_x(),
										 -vector.get_destination_y());
		shape[0].color = get_color(vector.get_color());
		shape[1].color = get_color(vector.get_color());
		window.draw(shape);

		float tri_height = 12.0f * view.getSize().x / float(config.width);
		float tri_width = 9.0f * view.getSize().x / float(config.width);
		sf::Vector2f destination(vector.get_destination_x(), -vector.get_destination_y());
		sf::Vector2f u(vector.get_destination_x() - vector.get_origin_x(),
					   -vector.get_destination_y() + vector.get_origin_y());
		u *= 1.0f / std::sqrt(u.x * u.x + u.y * u.y);
		sf::Vector2f v (-u.y, u.x);
		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		triangle.setPoint(0, destination);
		triangle.setPoint(1, destination - tri_height * u + tri_width / 2 * v);
		triangle.setPoint(2, destination - tri_height * u - tri_width / 2 * v);
		triangle.setFillColor(get_color(vector.get_color()));
		window.draw(triangle);
	}

	void Canvas::draw_polygon(const Polygon_plot& polygon)
	{
		unsigned n = polygon.size();
		sf::VertexArray shape(sf::LineStrip, n + 1);
		for(unsigned i = 0; i < n; ++i)
		{
			shape[i].position = sf::Vector2f(polygon[i].get_abscissa(),
											 -polygon[i].get_ordinate());
		}
		shape[n].position = sf::Vector2f(polygon[0].get_abscissa(),
										 -polygon[0].get_ordinate());
		for(unsigned i = 0; i <= n; ++i)
		{
			shape[i].color = get_color(polygon.get_lines_color());
		}
		window.draw(shape);
		for(unsigned i = 0; i < n; ++i)
		{
			draw_point(polygon[i]);
		}
	}

	void Canvas::draw_circle(const Circle_plot& circle)
	{
		unsigned nb_vertices = 64;
		float a = 4 * std::acos(0) / nb_vertices;
		sf::VertexArray shape(sf::LineStrip, nb_vertices + 1);
		for(unsigned i = 0; i < nb_vertices; ++i)
		{
			shape[i].position = sf::Vector2f(
					circle.get_center_x() + circle.get_radius() * std::cos(i * a),
					-circle.get_center_y() - circle.get_radius() * std::sin(i * a));
		}
		shape[nb_vertices].position = sf::Vector2f(
				circle.get_center_x() + circle.get_radius(), -circle.get_center_y());
		for(unsigned i = 0; i <= nb_vertices; ++i)
		{
			shape[i].color = get_color(circle.get_color());
		}
		window.draw(shape);
	}

	void Canvas::draw_line(const Line_plot& line)
	{
		float x1, y1, x2, y2;
		Coordinate a = line.get_a();
		Coordinate b = line.get_b();
		Coordinate c = line.get_c();
		if(line.get_b() == 0)
		{
			x1 = - c / a;
			x2 = - c / a;
			y1 = - view.getCenter().y + view.getSize().y / 2;
			y2 = - view.getCenter().y - view.getSize().y / 2;
		}
		else
		{
			x1 = view.getCenter().x - view.getSize().x / 2;
			x2 = view.getCenter().x + view.getSize().x / 2;
			y1 = -(a * x1 + c) / b;
			y2 = -(a * x2 + c) / b;
		}

		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(x1, -y1);
		shape[1].position = sf::Vector2f(x2, -y2);
		shape[0].color = get_color(line.get_color());
		shape[1].color = get_color(line.get_color());
		window.draw(shape);
	}

	void Canvas::draw_text(const Text_plot& text)
	{
		sf::Text shape;
		shape.setFont(config.font);
		unsigned size = text.get_size();
		shape.setCharacterSize(size);
		shape.setString(text.get_content());

		float text_width = shape.getLocalBounds().width;
		float ratio = view.getSize().x / float(config.width);
		shape.setScale(ratio, ratio);

		shape.setFillColor(get_color(text.get_color()));
		shape.setOutlineColor(config.colors[BACKGROUND_COLOR]);
		shape.setOutlineThickness(2);

		float text_offset_x = text.get_offset_x() * ratio;
		float text_offset_y = text.get_offset_y() * ratio;
		shape.move(text.get_abscissa() + text_offset_x - text_width * ratio / 2,
				   -text.get_ordinate() - text_offset_y - float(size) * ratio / 2);
		window.draw(shape);
	}
}