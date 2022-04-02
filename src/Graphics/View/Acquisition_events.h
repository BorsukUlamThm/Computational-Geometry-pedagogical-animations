#ifndef ALPHA_ACQUISITION_EVENTS_H
#define ALPHA_ACQUISITION_EVENTS_H

#include "Acquisition_canvas.h"


namespace gr
{
void Acquisition_canvas::handle_events()
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
                config.width = event.size.width;
                config.height = event.size.height;
                setup_bounding_box();
                setup_view();
                break;

            case sf::Event::MouseButtonPressed:
                mouse_button_pressed_event(event);
                break;

            case sf::Event::MouseWheelScrolled:
                mouse_wheel_scrolled_event(event);
                break;

            case sf::Event::MouseButtonReleased:
                mouse_button_released_event(event);
                break;

            case sf::Event::MouseMoved:
                mouse_moved_event(event);
                break;

            case sf::Event::KeyPressed:
                key_pressed_event(event);
                break;

            default:
                break;
        }
    }
}

void Acquisition_canvas::handle_point(Coordinate x, Coordinate y)
{
    Acquisition acquisition = buffer[index];
    switch(state)
    {
        case BEGIN_ACQ:
        case END_ACQ:
            break;

        case POINT_ACQ1:
            acquisitions.add_point(x, y,
                                   acquisition.point().get_color(),
                                   acquisition.point().get_radius());
            break;

        case SEGMENT_ACQ1:
            acquisitions.add_point(x, y,
                                   acquisition.segment().get_end_points_color());
            state = SEGMENT_ACQ2;
            break;

        case SEGMENT_ACQ2:
            Point_plt p = acquisitions.get_last_plot().point();
            Point_plt q (x, y, acquisition.segment().get_end_points_color());
            acquisitions.erase_last_plot();
            acquisitions.add_segment(p, q, acquisition.segment().get_line_color());
            state = SEGMENT_ACQ1;
            break;
    }
}

void Acquisition_canvas::key_pressed_event(const sf::Event& event)
{
    switch(event.key.code)
    {
        case sf::Keyboard::Enter:
            index++;
            set_next_state();
            break;

        case sf::Keyboard::Space:
            Coordinate x;
            Coordinate y;
            acquire_point(x, y);
            handle_point(x, y);
            break;

        default:
            break;
    }
}
}

#endif //ALPHA_ACQUISITION_EVENTS_H
