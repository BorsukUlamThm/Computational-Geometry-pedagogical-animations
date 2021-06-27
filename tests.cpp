#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/Graphics/View/View.h"
#include "src/Algorithms/Model/Point_2.h"
#include "src/Algorithms/Model/Polygon_2.h"

void main1()
{
    gr::Point a(0, 0);
    gr::Point b(0, 1);
    gr::Point c(1, 0);
    gr::Point d(1, 1);
    gr::Segment s(a, d);

    gr::Figure figure;
    figure.add_point(a);
    figure.add_point(b);
    figure.add_point(c);
    figure.add_point(d);
    figure.add_vector(a, d, sf::Color::Red);
    figure.add_vector(b, c, sf::Color::Red);
    figure.add_text("a", a);
    figure.add_text("b", b);
    figure.add_text("c", c);
    figure.add_text("d", d);
    figure.add_text("segment", s);

    gr::Canvas canvas;
    canvas.display_figure(figure);
}

int main()
{
    main1();

    return 0;
}

