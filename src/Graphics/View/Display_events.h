#pragma once

/** @cond */
#include <cmath>
/** @endcond */
#include "Display_canvas.h"


namespace gr
{
void Display_canvas::handle_events()
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

void Display_canvas::next_slide()
{
    if(slide_index < nb_slides - 1)
    {
        slide_index++;
    }
}

void Display_canvas::prev_slide()
{
    if(slide_index > 0)
    {
        slide_index--;
    }
}

void Display_canvas::key_pressed_event(const sf::Event& event)
{
    float index_fraction = float(nb_slides) / 10;
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

        case sf::Keyboard::Escape:
            window.clear();
            window.close();
            break;

        default:
            break;
    }
}
}