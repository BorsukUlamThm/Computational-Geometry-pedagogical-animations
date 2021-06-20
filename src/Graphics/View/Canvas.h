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
    unsigned width = 600;
    unsigned height = 600;
    unsigned margin = 20;
    std::string title = "Canvas";

    float zoom = 1;
    float zoom_factor = 1.1;
    int offset_x = 0;
    int offset_y = 0;
    int hold_x = 0;
    int hold_y = 0;
    int hold_offset_x = 0;
    int hold_offset_y = 0;

    enum Mouse_button {NONE, LEFT, RIGHT, MIDDLE, PREV, NEXT};
    Mouse_button mouse_button = NONE;

    sf::RenderWindow window;
    sf::View view;
    Bounding_box boundingBox;

public:
    Canvas() = default;
    ~Canvas() = default;

    void display_figure(const Figure& figure);

private:
    void open();
    void setup_view();
    void manage_events();

    void draw_figure(const Figure& figure);
    void draw_point(const Point& point);
    void draw_segment(const Segment& segment);
    void draw_polygon(const Polygon& polygon);
};

void Canvas::display_figure(const Figure& figure)
{
    boundingBox = figure.get_bounding_box();
    open();
    setup_view();
    while(window.isOpen())
    {
        manage_events();
        draw_figure(figure);
        window.display();
    }
}

void Canvas::open()
{
    window.create(sf::VideoMode(width, height), title);
}

void Canvas::setup_view()
{
    Coordinate xm = boundingBox.get_min_abscissa();
    Coordinate xM = boundingBox.get_max_abscissa();
    Coordinate ym = boundingBox.get_min_ordinate();
    Coordinate yM = boundingBox.get_max_ordinate();
//    view.setCenter((xm + xM) / 2, (ym + yM) / 2);

    float window_format = float(width) / float(height);
    float figure_format = (xM - xm) / (yM - ym);
    if(window_format < figure_format)
    {
        float ratio = (xM - xm) / float(width) / zoom;
        view.setCenter(-ratio * float(offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * float(offset_y + hold_offset_y) + (ym + yM) / 2);
        float margin_offset = float(margin) * 2 * ratio;
        view.setSize(margin_offset + (xM - xm) / zoom,
                     margin_offset + (xM - xm) / window_format / zoom);
    }
    else
    {
        float ratio = (xM - xm) / float(width) / zoom;
        view.setCenter(-ratio * float(offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * float(offset_y + hold_offset_y) + (ym + yM) / 2);
        float margin_offset = float(margin) * 2 * ratio;
        view.setSize(margin_offset + (yM - ym) * window_format / zoom,
                     margin_offset + (yM - ym) / zoom);
    }

    window.setView(view);
}

void Canvas::manage_events()
{
    sf::Event event{};
    while(window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                width = event.size.width;
                height = event.size.height;
                setup_view();
                break;

            case sf::Event::MouseWheelScrolled:
                if(event.mouseWheelScroll.delta > 0)
                {
                    zoom *= zoom_factor;
                }
                else
                {
                    zoom /= zoom_factor;
                }
                setup_view();
                break;

            case sf::Event::MouseButtonPressed:
                if(mouse_button == NONE)
                {
                    switch(event.mouseButton.button)
                    {
                        case sf::Mouse::Left:
                            mouse_button = LEFT;
                            hold_x = event.mouseButton.x;
                            hold_y = event.mouseButton.y;
                            break;
                        case sf::Mouse::Right:
                            mouse_button = RIGHT;
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
                break;

            case sf::Event::MouseButtonReleased:
                switch(mouse_button)
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
                break;

            case sf::Event::MouseMoved:
                switch(mouse_button)
                {
                    case LEFT:
                        hold_offset_x = event.mouseMove.x - hold_x;
                        hold_offset_y = event.mouseMove.y - hold_y;
                        setup_view();
                        break;
                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
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
    float radius = point.get_radius() * view.getSize().x / float(width);
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
