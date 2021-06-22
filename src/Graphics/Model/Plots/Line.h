#ifndef ALPHA_LINE_H
#define ALPHA_LINE_H

#include <SFML/Graphics.hpp>
#include "../Global_variables.h"


namespace gr
{
class Line
{
private:
    // line equation : ax + by + c = 0
    Coordinate a{};
    Coordinate b{};
    Coordinate c{};
    sf::Color color = DEFAULT_PLOT_COLOR;

public:
    Line() = default;
    Line(const Coordinate& a, const Coordinate& b, const Coordinate& c,
         const sf::Color& col = DEFAULT_PLOT_COLOR);
    Line(const Segment& segment, sf::Color col = DEFAULT_PLOT_COLOR);
    Line(const Point& point1, const Point& point2,
         sf::Color col = DEFAULT_PLOT_COLOR);
    Line(const Coordinate& x1, const Coordinate& y1,
         const Coordinate& x2, const Coordinate& y2,
         const sf::Color& col = DEFAULT_PLOT_COLOR);
    Line(const Line& other);
    ~Line() = default;

    Coordinate get_a() const;
    Coordinate get_b() const;
    Coordinate get_c() const;
    sf::Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream&is, Line& line);
};

Line::Line(const Coordinate& a, const Coordinate& b, const Coordinate& c,
           const sf::Color& col)
{
    this-> a = Coordinate(a);
    this-> b = Coordinate(b);
    this-> c = Coordinate(c);
    color = col;
}

Line::Line(const Segment& segment, sf::Color col)
{
    Coordinate x1 = segment.get_origin().get_abscissa();
    Coordinate y1 = segment.get_origin().get_ordinate();
    Coordinate x2 = segment.get_destination().get_abscissa();
    Coordinate y2 = segment.get_destination().get_ordinate();
    Line(x1, y1, x2, y2, col);
}

Line::Line(const Point& point1, const Point& point2, sf::Color col)
{
    Coordinate x1 = point1.get_abscissa();
    Coordinate y1 = point1.get_ordinate();
    Coordinate x2 = point2.get_abscissa();
    Coordinate y2 = point2.get_ordinate();
    Line(x1, y1, x2, y2, col);
}

Line::Line(const Coordinate& x1, const Coordinate& y1,
           const Coordinate& x2, const Coordinate& y2,
           const sf::Color& col)
{
    a = y2 - y1;
    b = x1 - x2;
    c = - a * x1 - b * y1;
    color = col;
}

Line::Line(const Line& other)
{
    a = Coordinate(other.a);
    b = Coordinate(other.b);
    c = Coordinate(other.c);
    color = other.color;
}

Coordinate Line::get_a() const
{
    return a;
}

Coordinate Line::get_b() const
{
    return b;
}

Coordinate Line::get_c() const
{
    return c;
}

sf::Color Line::get_color() const
{
    return color;
}

Coordinate Line::get_min_abscissa() const
{
    return MAX_COORDINATE;
}

Coordinate Line::get_max_abscissa() const
{
    return MIN_COORDINATE;
}

Coordinate Line::get_min_ordinate() const
{
    return MAX_COORDINATE;
}

Coordinate Line::get_max_ordinate() const
{
    return MIN_COORDINATE;
}

std::ostream& operator<<(std::ostream& os, const Line& line)
{
    os << LINE_NAME << " " << line.get_a()
                    << " " << line.get_b()
                    << " " << line.get_c();
    return os;
}

std::istream& operator>>(std::istream& is, Line& line)
{
    is >> line.a >> line.b >> line.c;
    return is;
}
}


#endif //ALPHA_LINE_H
