#ifndef ALPHA_HANDLE_EVENTS_H
#define ALPHA_HANDLE_EVENTS_H

#include <cmath>
#include "Canvas.h"


namespace gr
{
void Canvas::handle_events()
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
                zoom *= std::pow(zoom_factor, event.mouseWheelScroll.delta);
                setup_view();
                break;

            case sf::Event::MouseButtonPressed:
                mouse_button_pressed_event(event);
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

void Canvas::next_slide()
{
    if(slide_index < nb_slides - 1)
    {
        slide_index++;
    }
}

void Canvas::prev_slide()
{
    if(slide_index > 0)
    {
        slide_index--;
    }
}

void Canvas::mouse_button_pressed_event(const sf::Event& event)
{
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
                offset_x = 0;
                offset_y = 0;
                hold_x = 0;
                hold_y = 0;
                hold_offset_y = 0;
                hold_offset_x = 0;
                zoom = 1;
                break;

            case sf::Mouse::Middle:
                mouse_button = MIDDLE;
                break;

            case sf::Mouse::XButton1:
                mouse_button = PREV;
                prev_slide();
                break;

            case sf::Mouse::XButton2:
                mouse_button = NEXT;
                next_slide();
                break;

            default:
                break;
        }
    }
}

void Canvas::mouse_button_released_event(const sf::Event& event)
{
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
}

void Canvas::mouse_moved_event(const sf::Event& event)
{
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
}

void Canvas::key_pressed_event(const sf::Event& event)
{
    switch(event.key.code)
    {
        case sf::Keyboard::Right:
        case sf::Keyboard::Space:
            next_slide();
            break;

        case sf::Keyboard::Left:
            prev_slide();
            break;

        case sf::Keyboard::Enter:
            slide_index = 0;
            break;

        default:
            break;
    }
}
}

#endif //ALPHA_HANDLE_EVENTS_H
