#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/Graphics/View/View.h"
#include "src/Algorithms/Model/Point_2.h"
#include "src/Algorithms/Model/Polygon_2.h"


int main()
{
    gr::Acquisition_canvas canvas;
    canvas.add_point_acquisition();
    canvas.add_point_acquisition(sf::Color::Red);
    canvas.add_segment_acquisition();
    canvas.add_segment_acquisition(sf::Color::Green, sf::Color::Blue);
    gr::Figure figure = canvas.acquire_buffer();

    return 0;
}

