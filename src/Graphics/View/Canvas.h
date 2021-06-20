#ifndef ALPHA_CANVAS_H
#define ALPHA_CANVAS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Model/Figure.h"

namespace gr
{
class Canvas
{
private:
    unsigned width = 800;
    unsigned height = 600;
    std::string title = "Canvas";

    sf::RenderWindow window;

public:
    Canvas() = default;
    ~Canvas() = default;

    void display_figure(const Figure& figure);

private:
    void open();
    void draw_figure(const Figure& figure);
    void draw_point(const Point& point);
    void draw_segment(const Segment& segment);
    void draw_polygon(const Polygon& polygon);
};

void Canvas::display_figure(const Figure& figure)
{
    open();
    while(window.isOpen())
    {
        sf::Event event{};
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        draw_figure(figure);
        window.display();
    }
}

void Canvas::open()
{
    window.setFramerateLimit(60);
    window.create(sf::VideoMode(width, height), title);
}

void Canvas::draw_figure(const Figure& figure)
{
    window.clear(sf::Color::White);
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
        }
    }
}

void Canvas::draw_point(const Point& point)
{
    Coordinate radius = 3;
    sf::CircleShape shape(radius);
    shape.move(point.get_abscissa() - radius,
               point.get_ordinate() - radius);
    shape.setFillColor(sf::Color::Black);
    window.draw(shape);
}

void Canvas::draw_segment(const Segment& segment)
{
    sf::VertexArray shape(sf::LineStrip, 2);
    shape[0].position = sf::Vector2f(segment.get_origin().get_abscissa(),
                                     segment.get_origin().get_ordinate());
    shape[1].position = sf::Vector2f(segment.get_destination().get_abscissa(),
                                     segment.get_destination().get_ordinate());
    shape[0].color = sf::Color::Black;
    shape[1].color = sf::Color::Black;
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
                                         polygon[i].get_ordinate());
    }
    shape[n].position = sf::Vector2f(polygon[0].get_abscissa(),
                                     polygon[0].get_ordinate());
    for(unsigned i = 0; i <= n; ++i)
    {
        shape[i].color = sf::Color::Black;
    }
    window.draw(shape);
    for(unsigned i = 0; i < n; ++i)
    {
        draw_point(polygon[i]);
    }
}

}


#endif //ALPHA_CANVAS_H
