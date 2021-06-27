#ifndef ALPHA_VECTOR_H
#define ALPHA_VECTOR_H

#include "Segment.h"


namespace gr
{
class Vector
{
private:
    Coordinate origin_x;
    Coordinate origin_y;
    Coordinate destination_x;
    Coordinate destination_y;
    sf::Color color = DEFAULT_PLOT_COLOR;

public:
    Vector() = default;
    Vector(const Coordinate& ogn_x, const Coordinate& ogn_y,
           const Coordinate& dst_x, const Coordinate& dst_y,
           const sf::Color& col = DEFAULT_PLOT_COLOR);
    Vector(const Point& ogn, const Point& dst,
           const sf::Color& col = DEFAULT_PLOT_COLOR);
    explicit Vector(const Segment& segment, const sf::Color& col = DEFAULT_PLOT_COLOR);
    ~Vector() = default;

    Coordinate get_origin_x() const;
    Coordinate get_origin_y() const;
    Coordinate get_destination_x() const;
    Coordinate get_destination_y() const;
    sf::Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Vector& vector);
};

Vector::Vector(const Coordinate& ogn_x, const Coordinate& ogn_y,
               const Coordinate& dst_x, const Coordinate& dst_y,
               const sf::Color& col)
{
    origin_x = ogn_x;
    origin_y = ogn_y;
    destination_x = dst_x;
    destination_y = dst_y;
    color = col;
}

Vector::Vector(const Point& ogn, const Point& dst, const sf::Color& col)
{
    origin_x = ogn.get_abscissa();
    origin_y = ogn.get_ordinate();
    destination_x = dst.get_abscissa();
    destination_y = dst.get_ordinate();
    color = col;
}

Vector::Vector(const Segment& segment, const sf::Color& col)
{
    origin_x = segment.get_origin().get_abscissa();
    origin_y = segment.get_origin().get_ordinate();
    destination_x = segment.get_destination().get_abscissa();
    destination_y = segment.get_destination().get_ordinate();
    color = col;
}

Coordinate Vector::get_origin_x() const
{
    return origin_x;
}

Coordinate Vector::get_origin_y() const
{
    return origin_y;
}

Coordinate Vector::get_destination_x() const
{
    return destination_x;
}

Coordinate Vector::get_destination_y() const
{
    return destination_y;
}

sf::Color Vector::get_color() const
{
    return color;
}

Coordinate Vector::get_min_abscissa() const
{
    return std::min(origin_x, destination_x);
}

Coordinate Vector::get_max_abscissa() const
{
    return std::max(origin_x, destination_x);
}

Coordinate Vector::get_min_ordinate() const
{
    return std::min(origin_y, destination_y);
}

Coordinate Vector::get_max_ordinate() const
{
    return std::max(origin_y, destination_y);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector)
{
    os << VECTOR_NAME << " " << vector.get_origin_x()
                      << " " << vector.get_origin_y()
                      << " " << vector.get_destination_x()
                      << " " << vector.get_destination_y();
    return os;
}

std::istream& operator>>(std::istream& is, Vector& vector)
{
    is >> vector.origin_x >> vector.origin_y
       >> vector.destination_x >> vector.destination_y;
    return is;
}
}


#endif //ALPHA_VECTOR_H
