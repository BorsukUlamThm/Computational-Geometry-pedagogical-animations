#pragma once

#include "Canvas.h"
#include "Canvas_events.h"


namespace gr
{
class Display_canvas : public Canvas
{
private:
    unsigned nb_slides = 0;
    unsigned slide_index = 0;

public:
    Display_canvas() = default;
    ~Display_canvas() = default;

    void display_figure(Figure& figure);
    void display_slide_show(Slide_show& slide_show);

private:
    void handle_events();
    void next_slide();
    void prev_slide();
    void key_pressed_event(const sf::Event& event);
};

void Display_canvas::display_figure(Figure& figure)
{
    figure.make_bounding_box();
    bounding_box = figure.get_bounding_box();
    open();
    setup_view();
    while(window.isOpen())
    {
        handle_events();
        draw_figure(figure);
        window.display();
    }
}

void Display_canvas::display_slide_show(Slide_show& slide_show)
{
    slide_show[0].make_bounding_box();
    bounding_box = slide_show[0].get_bounding_box();
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
}