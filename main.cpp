#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/Graphics/View/Canvas.h"

int main()
{
    gr::Point a(100, 100);
    gr::Point b(200, 200);
    gr::Point c(180, 180);
    gr::Point d(180, 200);
    gr::Point e(150, 150);
    gr::Polygon P({a, b, c, d, e});

    gr::Figure figure;
    figure.add_polygon(P);
    gr::Canvas canvas;
    canvas.display_figure(figure);

    return 0;
}