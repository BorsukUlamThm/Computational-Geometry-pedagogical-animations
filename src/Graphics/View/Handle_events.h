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
                mouse_wheel_scrolled_event(event);
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

void Canvas::mouse_wheel_scrolled_event(const sf::Event& event)
{
    float zoom_ratio = std::pow(zoom_factor, event.mouseWheelScroll.delta);
    zoom *= zoom_ratio;

    float zoom_center_x = float(width) / 2 + offset_x;
    float zoom_center_y = float(height) / 2 + offset_y;
    float x = float(event.mouseWheelScroll.x);
    float y = float(event.mouseWheelScroll.y);
    offset_x += (x - zoom_center_x) * (1 - zoom_ratio);
    offset_y += (y - zoom_center_y) * (1 - zoom_ratio);

    setup_view();
}

void Canvas::mouse_button_pressed_event(const sf::Event& event)
{
    if(mouse_button == NONE)
    {
        switch(event.mouseButton.button)
        {
            case sf::Mouse::Left:
                mouse_button = LEFT;
                hold_x = float(event.mouseButton.x);
                hold_y = float(event.mouseButton.y);
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
            hold_offset_x = float(event.mouseMove.x) - hold_x;
            hold_offset_y = float(event.mouseMove.y) - hold_y;
            setup_view();
            break;

        default:
            break;
    }
}

void Canvas::key_pressed_event(const sf::Event& event)
{
    float index_fraction = float(nb_slides) / 10;
    std::cout << event.key.code << std::endl;
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
        case sf::Keyboard::Num0:
        case sf::Keyboard::Numpad0:
            slide_index = 0;
            break;

        case sf::Keyboard::Num1:
        case sf::Keyboard::Numpad1:
            slide_index = unsigned(index_fraction);
            break;

        case sf::Keyboard::Num2:
        case sf::Keyboard::Numpad2:
            slide_index = unsigned(2 * index_fraction);
            break;

        case sf::Keyboard::Num3:
        case sf::Keyboard::Numpad3:
            slide_index = unsigned(3 * index_fraction);
            break;

        case sf::Keyboard::Num4:
        case sf::Keyboard::Numpad4:
        case sf::Keyboard::Quote:
            slide_index = unsigned(4 * index_fraction);
            break;

        case sf::Keyboard::Num5:
        case sf::Keyboard::Numpad5:
            slide_index = unsigned(5 * index_fraction);
            break;

        case sf::Keyboard::Num6:
        case sf::Keyboard::Numpad6:
        case sf::Keyboard::Hyphen:
            slide_index = unsigned(6 * index_fraction);
            break;

        case sf::Keyboard::Num7:
        case sf::Keyboard::Numpad7:
            slide_index = unsigned(7 * index_fraction);
            break;

        case sf::Keyboard::Num8:
        case sf::Keyboard::Numpad8:
            slide_index = unsigned(8 * index_fraction);
            break;

        case sf::Keyboard::Num9:
        case sf::Keyboard::Numpad9:
            slide_index = unsigned(9 * index_fraction);
            break;

        case sf::Keyboard::BackSpace:
            slide_index = nb_slides - 1;
            break;

        default:
            break;
    }
}
}

#endif //ALPHA_HANDLE_EVENTS_H
