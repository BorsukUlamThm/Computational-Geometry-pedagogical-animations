#ifndef ALPHA_POINT_H
#define ALPHA_POINT_H

namespace gr
{
class Point
{
private:
    Coordinate abscissa{};
    Coordinate ordinate{};

public:
    Point() = default;
    Point(const Coordinate& x, const Coordinate& y);
    Point(const Point& other);
    ~Point() = default;

    Coordinate get_abscissa() const;
    Coordinate get_ordinate() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Point& point);
};

Point::Point(const Coordinate &x, const Coordinate &y)
{
    abscissa = Coordinate(x);
    ordinate = Coordinate(y);
}

Point::Point(const Point& other) {
    abscissa = Coordinate(other.get_abscissa());
    ordinate = Coordinate(other.get_ordinate());
}

Coordinate Point::get_abscissa() const {
    return abscissa;
}

Coordinate Point::get_ordinate() const {
    return ordinate;
}

Coordinate Point::get_min_abscissa() const
{
    return abscissa;
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
