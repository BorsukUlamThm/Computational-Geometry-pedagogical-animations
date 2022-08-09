#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Graphics/Model/Global_variables.h"


namespace gr
{
class Circle_plt
{
private:
    Coordinate center_x{};
    Coordinate center_y{};
    Coordinate radius{};
    Color color = DEFAULT_PLOT_COLOR;

public:
    Circle_plt() = default;
    Circle_plt(const Coordinate& x, const Coordinate& y, const Coordinate& rad,
           Color col = DEFAULT_PLOT_COLOR);
    Circle_plt(const Circle_plt& other);
    ~Circle_plt() = default;

    Coordinate get_center_x() const;
    Coordinate get_center_y() const;
    Coordinate get_radius() const;
    Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Circle_plt& circle);
};

Circle_plt::Circle_plt(const Coordinate& x, const Coordinate& y,
               const Coordinate& rad, Color col)
{
    center_x = Coordinate(x);
    center_y = Coordinate(y);
    radius = Coordinate(rad);
    color = col;
}

Circle_plt::Circle_plt(const Circle_plt& other)
{
    center_x = Coordinate(other.center_x);
    center_y = Coordinate(other.center_y);
    radius = Coordinate(other.radius);
    color = other.color;
}

Coordinate Circle_plt::get_center_x() const
{
    return center_x;
}

Coordinate Circle_plt::get_center_y() const
{
    return  center_y;
}

Coordinate Circle_plt::get_radius() const
{
    return radius;
}

Color Circle_plt::get_color() const
{
    return color;
}

Coordinate Circle_plt::get_min_abscissa() const
{
    return center_x - radius;
}

Coordinate Circle_plt::get_max_abscissa() const
{
    return center_x + radius;
}

Coordinate Circle_plt::get_min_ordinate() const
{
    return center_y - radius;
}

Coordinate Circle_plt::get_max_ordinate() const
{
    return center_y + radius;
}

std::ostream& operator<<(std::ostream& os, const Circle_plt& circle)
{
    os << CIRCLE_NAME << " " << circle.get_center_x()
                      << " " << circle.get_center_y()
                      << " " << circle.get_radius();
    return os;
}

std::istream& operator>>(std::istream& is, Circle_plt& circle)
{
    is >> circle.center_x >> circle.center_y >> circle.radius;
    return is;
}
}