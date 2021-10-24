#include "src/Graphics/View/View.h"
#include "src/Algorithms/Algorithms.h"


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

