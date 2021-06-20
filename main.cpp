#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/Graphics/View/Canvas.h"

int main()
{
    gr::Point a(100, 300);
    gr::Point b(200, 300);
    gr::Point c(300, 200);
    gr::Point d(300, 100);
    gr::Point e(100, 200);
    gr::Polygon P({a, b, c, d, e});

    gr::Figure figure;
    figure.add_polygon(P);
    gr::Canvas canvas;
    canvas.display_figure(figure);

    return 0;
}