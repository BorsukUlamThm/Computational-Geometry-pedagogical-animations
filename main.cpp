#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "src/Graphics/View/View.h"
#include "src/Algorithms/Model/Point_2.h"
#include "src/Algorithms/Model/Polygon_2.h"

int main()
{
    typedef alg::Point_2<int> Point;
    typedef alg::Polygon_2<int> Polygon;

    Point p(0, 0);
    Point q(1, 1);
    Polygon P(p, q);

}