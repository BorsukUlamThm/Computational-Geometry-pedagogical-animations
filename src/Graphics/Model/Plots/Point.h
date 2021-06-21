#ifndef ALPHA_POINT_H
#define ALPHA_POINT_H

#include <SFML/Graphics.hpp>


namespace gr
{
class Point
{
private:
    Coordinate abscissa{};
    Coordinate ordinate{};
    sf::Color color = DEFAULT_PLOT_COLOR;
    float radius = 3;

public:
    Point() = default;
    Point(const Coordinate& x, const Coordinate& y,
          const sf::Color& col = DEFAULT_PLOT_COLOR, float rad = 3);
    Point(const Point& other);
    ~Point() = default;

    Coordinate get_abscissa() const;
    Coordinate get_ordinate() const;
    sf::Color get_color() const;
    float get_radius() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Point& point);
};

Point::Point(const Coordinate &x, const Coordinate &y,
             const sf::Color& col, float rad)
{
    abscissa = Coordinate(x);
    ordinate = Coordinate(y);
    color = col;
    radius = rad;
}

Point::Point(const Point& other)
{
    abscissa = Coordinate(other.abscissa);
    ordinate = Coordinate(other.ordinate);
    color = other.color;
}

Coordinate Point::get_abscissa() const
{
    return abscissa;
}

Coordinate Point::get_ordinate() const
{
    return ordinate;
}

Coordinate Point::get_min_abscissa() const
{
    return abscissa;
}

sf::Color Point::get_color() const
{
    return color;
}

float Point::get_radius() const
{
    return radius;
}

Coordinate Point::get_max_abscissa() const
{
    return abscissa;
}

Coordinate Point::get_min_ordinate() const
{
    return ordinate;
}

Coordinate Point::get_max_ordinate() const
{
    return ordinate;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << POINT_NAME << " " << point.get_abscissa()
                     << " " << point.get_ordinate();
    return os;
}

std::istream& operator>>(std::istream& is, Point& point)
{
    is >> point.abscissa;
    is >> point.ordinate;
    return is;
}
}


#endif //ALPHA_POINT_H
