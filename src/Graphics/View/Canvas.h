#ifndef ALPHA_CANVAS_H
#define ALPHA_CANVAS_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Graphics/Model/Figure.h"
#include "Graphics/Model/Slide_show.h"

namespace gr
{
class Canvas
{
protected:
    sf::RenderWindow window;
    Bounding_box bounding_box;
    sf::View view;

    unsigned width = 1600;
    unsigned height = 900;
    unsigned margin = 20;
    std::string title = "Display";
    sf::Color background_color = DEFAULT_BACKGROUND_COLOR;

    float zoom = 1;
    float zoom_factor = 1.1;
    float offset_x = 0;
    float offset_y = 0;
    float hold_x = 0;
    float hold_y = 0;
    float hold_offset_x = 0;
    float hold_offset_y = 0;

    enum Mouse_button {NONE, LEFT, RIGHT, MIDDLE, PREV, NEXT};
    Mouse_button mouse_button = NONE;
    float mouse_x;
    float mouse_y;

public:
    Canvas() = default;
    ~Canvas() = default;

    unsigned get_width() const;
    unsigned get_height() const;
    unsigned get_margin() const;
    std::string get_title() const;
    sf::Color get_background_color() const;

    void set_width(unsigned& new_width);
    void set_height(unsigned& new_height);
    void set_margin(unsigned& new_margin);
    void set_title(const std::string& new_title);
    void set_background_color(const sf::Color& new_color);

protected:
    void open();
    void setup_view();

    void draw_figure(const Figure& figure);
    void draw_point(const Point_plt& point);
    void draw_segment(const Segment_plt& segment);
    void draw_vector(const Vector_plt& vector);
    void draw_polygon(const Polygon_plt& polygon);
    void draw_circle(const Circle_plt& circle);
    void draw_line(const Line_plt& line);
    void draw_text(const Text_plt& text);

    void mouse_wheel_scrolled_event(const sf::Event& event);
    void mouse_button_pressed_event(const sf::Event& event);
    void mouse_button_released_event(const sf::Event& event);
    void mouse_moved_event(const sf::Event& event);
};

unsigned Canvas::get_width() const
{
    return width;
}

unsigned Canvas::get_height() const
{
    return height;
}

unsigned Canvas::get_margin() const
{
    return margin;
}

std::string Canvas::get_title() const
{
    return title;
}

sf::Color Canvas::get_background_color() const
{
    return background_color;
}

void Canvas::set_width(unsigned& new_width)
{
    width = new_width;
}

void Canvas::set_height(unsigned& new_height)
{
    height = new_height;
}

void Canvas::set_margin(unsigned& new_margin)
{
    margin = new_margin;
}

void Canvas::set_title(const std::string& new_title)
{
    title = new_title;
}

void Canvas::set_background_color(const sf::Color& new_color)
{
    background_color = new_color;
}

void Canvas::open()
{
    window.clear(DEFAULT_BACKGROUND_COLOR);
    if(window.isOpen())
    {
        return;
    }
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(width, height), title,
                  sf::Style::Default, settings);
}

void Canvas::setup_view()
{
    Coordinate xm = bounding_box.get_min_abscissa();
    Coordinate xM = bounding_box.get_max_abscissa();
    Coordinate ym = -bounding_box.get_max_ordinate();
    Coordinate yM = -bounding_box.get_min_ordinate();

    if(xm == xM && ym == yM)
    {
        xm -= 1;
        xM += 1;
        ym -= 1;
        yM += 1;
    }

    float window_format = float(width) / float(height);
    float figure_format = (xM - xm) / (yM - ym);
    if(window_format < figure_format)
    {
        float margin_offset =
                2 * margin * (xM - xm) / zoom / float(width) / // NOLINT(cppcoreguidelines-narrowing-conversions)
                (1 - 2 * margin / float(width)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        view.setSize(margin_offset + (xM - xm) / zoom,
                     margin_offset + (xM - xm) / window_format / zoom);
        float ratio = view.getSize().x / float(width);
        view.setCenter(-ratio * (offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * (offset_y + hold_offset_y) + (ym + yM) / 2);
    }
    else
    {
        float margin_offset =
                2 * margin * (yM - ym) / zoom / float(height) / // NOLINT(cppcoreguidelines-narrowing-conversions)
                (1 - 2 * margin / float(height)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        view.setSize(margin_offset + (yM - ym) * window_format / zoom,
                     margin_offset + (yM - ym) / zoom);
        float ratio = view.getSize().x / float(width);
        view.setCenter(-ratio * (offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * (offset_y + hold_offset_y) + (ym + yM) / 2);
    }

    window.setView(view);
}
}


#endif //ALPHA_CANVAS_H
