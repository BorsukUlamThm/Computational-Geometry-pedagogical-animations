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
    figure.add_segment(a, d);
    figure.add_segment(b, c);
    figure.add_text("a", a);
    figure.add_text("b", b);
    figure.add_text("c", c);
    figure.add_text("d", d);
    figure.add_text("segment", s);

    gr::Canvas canvas;
    canvas.display_figure(figure);
}

void main2()
{
    sf::Font font;
    font.loadFromFile(DEFAULT_FONT);

    sf::Text text;
    text.setFont(font);
    text.setString("a");
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(2);
    text.move(100, 100);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    sf::View view;
    view.setCenter(100, 100);
    view.setSize(200, 200);
    window.setView(view);

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}


int main()
{
    main1();

    return 0;
}

