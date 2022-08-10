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
			figure[i]->draw(*this);
		}
	}

	void Point_shp::draw(Canvas& canvas) const
	{
		float ratio = canvas.view.getSize().x / float(canvas.config.width);
		float rad = radius * ratio;

		sf::CircleShape shape(rad);
		shape.move(abscissa - rad, -ordinate - rad);
		shape.setFillColor(canvas.get_color(color));

		canvas.window.draw(shape);
	}

	//	void Canvas::draw_point(const Point_shp& point)
	//	{
	//		float radius = point.get_radius() * view.getSize().x / float(config.width);
	//		sf::CircleShape shape(radius);
	//		shape.move(point.get_abscissa() - radius,
	//				   -point.get_ordinate() - radius);
	//		shape.setFillColor(get_color(point.get_color()));
	//		window.draw(shape);
	//	}

	void Segment_shp::draw(Canvas& canvas) const
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(origin.get_abscissa(),
										 -origin.get_ordinate());
		shape[1].position = sf::Vector2f(destination.get_abscissa(),
										 -destination.get_ordinate());
		shape[0].color = canvas.get_color(line_color);
		shape[1].color = canvas.get_color(line_color);

		canvas.window.draw(shape);
		origin.draw(canvas);
		destination.draw(canvas);
	}

	//	void Canvas::draw_segment(const Segment_shp& segment)
	//	{
	//		sf::VertexArray shape(sf::LineStrip, 2);
	//		shape[0].position = sf::Vector2f(segment.get_origin().get_abscissa(),
	//										 -segment.get_origin().get_ordinate());
	//		shape[1].position = sf::Vector2f(segment.get_destination().get_abscissa(),
	//										 -segment.get_destination().get_ordinate());
	//		shape[0].color = get_color(segment.get_line_color());
	//		shape[1].color = get_color(segment.get_line_color());
	//		window.draw(shape);
	//		draw_point(segment.get_origin());
	//		draw_point(segment.get_destination());
	//	}

	void Vector_shp::draw(gr::Canvas& canvas) const
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(origin_x, -origin_y);
		shape[1].position = sf::Vector2f(destination_x, -destination_y);
		shape[0].color = canvas.get_color(color);
		shape[1].color = canvas.get_color(color);
		canvas.window.draw(shape);

		float ratio = canvas.view.getSize().x / float(canvas.config.width);
		float tri_height = 12.0f * ratio;
		float tri_width = 9.0f * ratio;

		sf::Vector2f destination(destination_x, -destination_y);
		sf::Vector2f u(destination_x - origin_x, -destination_y + origin_y);
		u *= 1.0f / std::sqrt(u.x * u.x + u.y * u.y);
		sf::Vector2f v (-u.y, u.x);

		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		triangle.setPoint(0, destination);
		triangle.setPoint(1, destination - tri_height * u + tri_width / 2 * v);
		triangle.setPoint(2, destination - tri_height * u - tri_width / 2 * v);
		triangle.setFillColor(canvas.get_color(color));

		canvas.window.draw(triangle);
	}

	//	void Canvas::draw_vector(const Vector_shp& vector)
	//	{
	//		sf::VertexArray shape(sf::LineStrip, 2);
	//		shape[0].position = sf::Vector2f(vector.get_origin_x(),
	//										 -vector.get_origin_y());
	//		shape[1].position = sf::Vector2f(vector.get_destination_x(),
	//										 -vector.get_destination_y());
	//		shape[0].color = get_color(vector.get_color());
	//		shape[1].color = get_color(vector.get_color());
	//		window.draw(shape);
	//
	//		float tri_height = 12.0f * view.getSize().x / float(config.width);
	//		float tri_width = 9.0f * view.getSize().x / float(config.width);
	//		sf::Vector2f destination(vector.get_destination_x(), -vector.get_destination_y());
	//		sf::Vector2f u(vector.get_destination_x() - vector.get_origin_x(),
	//					   -vector.get_destination_y() + vector.get_origin_y());
	//		u *= 1.0f / std::sqrt(u.x * u.x + u.y * u.y);
	//		sf::Vector2f v (-u.y, u.x);
	//		sf::ConvexShape triangle;
	//		triangle.setPointCount(3);
	//		triangle.setPoint(0, destination);
	//		triangle.setPoint(1, destination - tri_height * u + tri_width / 2 * v);
	//		triangle.setPoint(2, destination - tri_height * u - tri_width / 2 * v);
	//		triangle.setFillColor(get_color(vector.get_color()));
	//		window.draw(triangle);
	//	}

	void Polygon_shp::draw(Canvas& canvas) const
	{
		unsigned n = size();
		sf::VertexArray shape(sf::LineStrip, n + 1);
		for(unsigned i = 0; i < n; ++i)
		{
			shape[i].position = sf::Vector2f(vertices[i].get_abscissa(),
											 -vertices[i].get_ordinate());
		}
		shape[n].position = sf::Vector2f(vertices[0].get_abscissa(),
										 -vertices[0].get_ordinate());

		for(unsigned i = 0; i <= n; ++i)
		{
			shape[i].color = canvas.get_color(lines_color);
		}
		canvas.window.draw(shape);

		for(unsigned i = 0; i < n; ++i)
		{
			vertices[i].draw(canvas);
		}
	}

	//	void Canvas::draw_polygon(const Polygon_shp& polygon)
	//	{
	//		unsigned n = polygon.size();
	//		sf::VertexArray shape(sf::LineStrip, n + 1);
	//		for(unsigned i = 0; i < n; ++i)
	//		{
	//			shape[i].position = sf::Vector2f(polygon[i].get_abscissa(),
	//											 -polygon[i].get_ordinate());
	//		}
	//		shape[n].position = sf::Vector2f(polygon[0].get_abscissa(),
	//										 -polygon[0].get_ordinate());
	//		for(unsigned i = 0; i <= n; ++i)
	//		{
	//			shape[i].color = get_color(polygon.get_lines_color());
	//		}
	//		window.draw(shape);
	//		for(unsigned i = 0; i < n; ++i)
	//		{
	//			draw_point(polygon[i]);
	//		}
	//	}

	void Circle_shp::draw(Canvas& canvas) const
	{
		unsigned nb_vertices = 64;
		float a = 4 * std::acos(0) / nb_vertices;
		sf::VertexArray shape(sf::LineStrip, nb_vertices + 1);
		for(unsigned i = 0; i < nb_vertices; ++i)
		{
			Coordinate x = center_x + radius * std::cos(i * a);
			Coordinate y = -center_y - radius * std::sin(i * a);
			shape[i].position = sf::Vector2f(x, y);
		}
		Coordinate x = center_x + radius;
		Coordinate y = -center_y;
		shape[nb_vertices].position = sf::Vector2f(x, y);

		for(unsigned i = 0; i <= nb_vertices; ++i)
		{
			shape[i].color = canvas.get_color(color);
		}
		canvas.window.draw(shape);
	}

//	void Canvas::draw_circle(const Circle_shp& circle)
//	{
//		unsigned nb_vertices = 64;
//		float a = 4 * std::acos(0) / nb_vertices;
//		sf::VertexArray shape(sf::LineStrip, nb_vertices + 1);
//		for(unsigned i = 0; i < nb_vertices; ++i)
//		{
//			shape[i].position = sf::Vector2f(
//					circle.get_center_x() + circle.get_radius() * std::cos(i * a),
//					-circle.get_center_y() - circle.get_radius() * std::sin(i * a));
//		}
//		shape[nb_vertices].position = sf::Vector2f(
//				circle.get_center_x() + circle.get_radius(), -circle.get_center_y());
//		for(unsigned i = 0; i <= nb_vertices; ++i)
//		{
//			shape[i].color = get_color(circle.get_color());
//		}
//		window.draw(shape);
//	}

	void Line_shp::draw(Canvas& canvas) const
	{
		float x1, y1, x2, y2;
		if(b == 0)
		{
			x1 = - c / a;
			x2 = - c / a;
			y1 = - canvas.view.getCenter().y + canvas.view.getSize().y / 2;
			y2 = - canvas.view.getCenter().y - canvas.view.getSize().y / 2;
		}
		else
		{
			x1 = canvas.view.getCenter().x - canvas.view.getSize().x / 2;
			x2 = canvas.view.getCenter().x + canvas.view.getSize().x / 2;
			y1 = -(a * x1 + c) / b;
			y2 = -(a * x2 + c) / b;
		}

		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(x1, -y1);
		shape[1].position = sf::Vector2f(x2, -y2);
		shape[0].color = canvas.get_color(color);
		shape[1].color = canvas.get_color(color);
		canvas.window.draw(shape);
	}

//	void Canvas::draw_line(const Line_shp& line)
//	{
//		float x1, y1, x2, y2;
//		Coordinate a = line.get_a();
//		Coordinate b = line.get_b();
//		Coordinate c = line.get_c();
//		if(line.get_b() == 0)
//		{
//			x1 = - c / a;
//			x2 = - c / a;
//			y1 = - view.getCenter().y + view.getSize().y / 2;
//			y2 = - view.getCenter().y - view.getSize().y / 2;
//		}
//		else
//		{
//			x1 = view.getCenter().x - view.getSize().x / 2;
//			x2 = view.getCenter().x + view.getSize().x / 2;
//			y1 = -(a * x1 + c) / b;
//			y2 = -(a * x2 + c) / b;
//		}
//
//		sf::VertexArray shape(sf::LineStrip, 2);
//		shape[0].position = sf::Vector2f(x1, -y1);
//		shape[1].position = sf::Vector2f(x2, -y2);
//		shape[0].color = get_color(line.get_color());
//		shape[1].color = get_color(line.get_color());
//		window.draw(shape);
//	}

	void Text_shp::draw(gr::Canvas& canvas) const
	{
		sf::Text shape;
		shape.setFont(canvas.config.font);
		shape.setCharacterSize(size);
		shape.setString(content);

		float text_width = shape.getLocalBounds().width;
		float ratio = canvas.view.getSize().x / float(canvas.config.width);
		shape.setScale(ratio, ratio);

		shape.setFillColor(canvas.get_color(color));
		shape.setOutlineColor(canvas.config.colors[BACKGROUND_COLOR]);
		shape.setOutlineThickness(2);

		float text_offset_x = offset_x * ratio;
		float text_offset_y = offset_y * ratio;
		shape.move(abscissa + text_offset_x - text_width * ratio / 2,
				   -ordinate - text_offset_y - float(size) * ratio / 2);
		canvas.window.draw(shape);
	}

//	void Canvas::draw_text(const Text_shp& text)
//	{
//		sf::Text shape;
//		shape.setFont(config.font);
//		unsigned size = text.get_size();
//		shape.setCharacterSize(size);
//		shape.setString(text.get_content());
//
//		float text_width = shape.getLocalBounds().width;
//		float ratio = view.getSize().x / float(config.width);
//		shape.setScale(ratio, ratio);
//
//		shape.setFillColor(get_color(text.get_color()));
//		shape.setOutlineColor(config.colors[BACKGROUND_COLOR]);
//		shape.setOutlineThickness(2);
//
//		float text_offset_x = text.get_offset_x() * ratio;
//		float text_offset_y = text.get_offset_y() * ratio;
//		shape.move(text.get_abscissa() + text_offset_x - text_width * ratio / 2,
//				   -text.get_ordinate() - text_offset_y - float(size) * ratio / 2);
//		window.draw(shape);
//	}
}