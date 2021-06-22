#ifndef ALPHA_CANVAS_H
#define ALPHA_CANVAS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Model/Figure.h"
#include "../Model/Slide_show.h"

namespace gr
{
class Canvas
{
private:
    sf::RenderWindow window;
    sf::View view;
    Bounding_box boundingBox;

    unsigned nb_slides = 0;
    unsigned slide_index = 0;

    unsigned width = 900;
    unsigned height = 900;
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

public:
    Canvas() = default;
    ~Canvas() = default;

    void display_figure(const Figure& figure);
    void display_slide_show(const Slide_show& slide_show);

private:
    void open();
    void setup_view();

    void handle_events();
    void next_slide();
    void prev_slide();
    void mouse_button_pressed_event(const sf::Event& event);
    void mouse_button_released_event(const sf::Event& event);
    void mouse_moved_event(const sf::Event& event);
    void key_pressed_event(const sf::Event& event);

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
        handle_events();
        draw_figure(figure);
        window.display();
    }
}

void Canvas::display_slide_show(const Slide_show& slide_show)
{
    boundingBox = slide_show[0].get_bounding_box();
    nb_slides = slide_show.nb_slides();
    open();
    setup_view();
    while(window.isOpen())
    {
        handle_events();
        draw_figure(slide_show[slide_index]);
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
    Coordinate ym = -boundingBox.get_max_ordinate();
    Coordinate yM = -boundingBox.get_min_ordinate();

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
        view.setCenter(-ratio * float(offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * float(offset_y + hold_offset_y) + (ym + yM) / 2);
    }
    else
    {
        float margin_offset =
                2 * margin * (yM - ym) / zoom / float(height) / // NOLINT(cppcoreguidelines-narrowing-conversions)
                (1 - 2 * margin / float(height)); // NOLINT(cppcoreguidelines-narrowing-conversions)
        view.setSize(margin_offset + (yM - ym) * window_format / zoom,
                     margin_offset + (yM - ym) / zoom);
        float ratio = view.getSize().x / float(width);
        view.setCenter(-ratio * float(offset_x + hold_offset_x) + (xm + xM) / 2,
                       -ratio * float(offset_y + hold_offset_y) + (ym + yM) / 2);
    }

    window.setView(view);
}
}


#endif //ALPHA_CANVAS_H
