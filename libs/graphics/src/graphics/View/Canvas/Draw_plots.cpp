#include "graphics/View/Canvas.h"
#include <cmath>


namespace graphics
{
	void Canvas::draw_figure(const Figure& figure)
	{
		window.clear(config.colors[BACKGROUND_COLOR]);
		for (unsigned i = 0; i < figure.nb_shapes(); ++i)
		{
			figure[i]->draw(*this);
		}
	}

	void Point_shp::draw(Canvas& canvas) const
	{
		float ratio = canvas.view.getSize().x / float(canvas.config.width);
		float rad = radius * ratio;

		sf::CircleShape shape(rad);
		shape.move(point.abscissa - rad, -point.ordinate - rad);
		shape.setFillColor(canvas.get_color(color));

		canvas.window.draw(shape);
	}

	void Segment_shp::draw(Canvas& canvas) const
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(segment.origin.abscissa,
										 -segment.origin.ordinate);
		shape[1].position = sf::Vector2f(segment.destination.abscissa,
										 -segment.destination.ordinate);
		shape[0].color = canvas.get_color(line_color);
		shape[1].color = canvas.get_color(line_color);

		canvas.window.draw(shape);

		Point_shp origin(segment.origin.abscissa,
						 segment.origin.ordinate,
						 endpoints_color);
		Point_shp destination(segment.destination.abscissa,
							  segment.destination.ordinate,
							  endpoints_color);
		origin.draw(canvas);
		destination.draw(canvas);
	}

	void Vector_shp::draw(graphics::Canvas& canvas) const
	{
		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(vector.origin.abscissa,
										 -vector.origin.ordinate);
		shape[1].position = sf::Vector2f(vector.destination.abscissa,
										 -vector.destination.ordinate);
		shape[0].color = canvas.get_color(color);
		shape[1].color = canvas.get_color(color);
		canvas.window.draw(shape);

		float ratio = canvas.view.getSize().x / float(canvas.config.width);
		float tri_height = 12.0f * ratio;
		float tri_width = 9.0f * ratio;

		sf::Vector2f destination(vector.destination.abscissa,
								 -vector.destination.ordinate);
		sf::Vector2f u(vector.destination.abscissa - vector.origin.abscissa,
					   -vector.destination.ordinate + vector.origin.ordinate);
		u *= 1.0f / std::sqrt(u.x * u.x + u.y * u.y);
		sf::Vector2f v(-u.y, u.x);

		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		triangle.setPoint(0, destination);
		triangle.setPoint(1, destination - tri_height * u + tri_width / 2 * v);
		triangle.setPoint(2, destination - tri_height * u - tri_width / 2 * v);
		triangle.setFillColor(canvas.get_color(color));

		canvas.window.draw(triangle);
	}

	void Polygon_shp::draw(Canvas& canvas) const
	{
		unsigned n = size();
		sf::VertexArray shape(sf::LineStrip, n + 1);
		for (unsigned i = 0; i < n; ++i)
		{
			shape[i].position = sf::Vector2f(vertices[i].abscissa,
											 -vertices[i].ordinate);
		}
		shape[n].position = sf::Vector2f(vertices[0].abscissa,
										 -vertices[0].ordinate);

		for (unsigned i = 0; i <= n; ++i)
		{
			shape[i].color = canvas.get_color(lines_color);
		}
		canvas.window.draw(shape);

		for (unsigned i = 0; i < n; ++i)
		{
			Point_shp point (vertices[i].abscissa, vertices[i].ordinate,
							 vertices_color);
			point.draw(canvas);
		}
	}

	void Circle_shp::draw(Canvas& canvas) const
	{
		unsigned nb_vertices = 64;
		float a = 4.f * float(std::acos(0)) / float(nb_vertices);
		sf::VertexArray shape(sf::LineStrip, nb_vertices + 1);

		float f = 0;
		for (unsigned i = 0; i < nb_vertices; ++i)
		{
			Coordinate x = circle.center_x + circle.radius * std::cos(f * a);
			Coordinate y = -circle.center_y - circle.radius * std::sin(f * a);
			shape[i].position = sf::Vector2f(x, y);

			f += 1;
		}
		Coordinate x = circle.center_x + circle.radius;
		Coordinate y = -circle.center_y;
		shape[nb_vertices].position = sf::Vector2f(x, y);

		for (unsigned i = 0; i <= nb_vertices; ++i)
		{
			shape[i].color = canvas.get_color(color);
		}
		canvas.window.draw(shape);
	}

	void Line_shp::draw(Canvas& canvas) const
	{
		float x1, y1, x2, y2;
		if (line.param_b == 0)
		{
			x1 = -line.param_c / line.param_a;
			x2 = -line.param_c / line.param_a;
			y1 = -canvas.view.getCenter().y + canvas.view.getSize().y / 2;
			y2 = -canvas.view.getCenter().y - canvas.view.getSize().y / 2;
		}
		else
		{
			x1 = canvas.view.getCenter().x - canvas.view.getSize().x / 2;
			x2 = canvas.view.getCenter().x + canvas.view.getSize().x / 2;
			y1 = -(line.param_a * x1 + line.param_c) / line.param_b;
			y2 = -(line.param_a * x2 + line.param_c) / line.param_b;
		}

		sf::VertexArray shape(sf::LineStrip, 2);
		shape[0].position = sf::Vector2f(x1, -y1);
		shape[1].position = sf::Vector2f(x2, -y2);
		shape[0].color = canvas.get_color(color);
		shape[1].color = canvas.get_color(color);
		canvas.window.draw(shape);
	}

	void Text_shp::draw(graphics::Canvas& canvas) const
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
		shape.move(point.abscissa + text_offset_x - text_width * ratio / 2,
				   -point.ordinate - text_offset_y - float(size) * ratio / 2);
		canvas.window.draw(shape);
	}
}