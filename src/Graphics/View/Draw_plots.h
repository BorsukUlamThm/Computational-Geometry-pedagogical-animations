#ifndef ALPHA_DRAW_PLOTS_H
#define ALPHA_DRAW_PLOTS_H

#include "Canvas.h"
#include <cmath>


namespace gr
{
void Canvas::draw_figure(const Figure& figure)
{
    window.clear(DEFAULT_BACKGROUND_COLOR);
    for(unsigned i = 0; i < figure.nb_plots(); ++i)
    {
        switch(figure[i].type())
        {
            case POINT:
                draw_point(figure[i].point());
                break;
            case SEGMENT:
                draw_segment(figure[i].segment());
                break;
            case POLYGON:
                draw_polygon(figure[i].polygon());
                break;
            case CIRCLE:
                draw_circle(figure[i].circle());
                break;
        }
    }
}

void Canvas::draw_point(const Point& point)
{
    float radius = point.get_radius() * view.getSize().x / float(width);
    sf::CircleShape shape(radius);
    shape.move(point.get_abscissa() - radius,
               -point.get_ordinate() - radius);
    shape.setFillColor(point.get_color());
    window.draw(shape);
}

void Canvas::draw_segment(const Segment& segment)
{
    sf::VertexArray shape(sf::LineStrip, 2);
    shape[0].position = sf::Vector2f(segment.get_origin().get_abscissa(),
                                     -segment.get_origin().get_ordinate());
    shape[1].position = sf::Vector2f(segment.get_destination().get_abscissa(),
                                     -segment.get_destination().get_ordinate());
    shape[0].color = segment.get_line_color();
    shape[1].color = segment.get_line_color();
    window.draw(shape);
    draw_point(segment.get_origin());
    draw_point(segment.get_destination());
}

void Canvas::draw_polygon(const Polygon& polygon)
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
        shape[i].color = polygon.get_lines_color();
    }
    window.draw(shape);
    for(unsigned i = 0; i < n; ++i)
    {
        draw_point(polygon[i]);
    }
}

void Canvas::draw_circle(const Circle& circle)
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
        shape[i].color = circle.get_color();
    }
    window.draw(shape);
}
}

#endif //ALPHA_DRAW_PLOTS_H
