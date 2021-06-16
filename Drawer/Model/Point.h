#ifndef ALPHA_POINT_H
#define ALPHA_POINT_H

#include "Plot.h"

class Point : public Plot
{
private:
    Point_coordinate abscissa{};
    Point_coordinate ordinate{};

public:
    Point() = default;
    Point(const Point_coordinate& x, const Point_coordinate& y);
    Point(const Point& other);

    Point_coordinate get_abscissa() const;
    Point_coordinate get_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Point& point);
};

Point::Point(const Point_coordinate &x, const Point_coordinate &y)
{
    abscissa = Point_coordinate(x);
    ordinate = Point_coordinate(y);
}

Point::Point(const Point& other) {
    abscissa = Point_coordinate(other.get_abscissa());
    ordinate = Point_coordinate(other.get_ordinate());
}

Point_coordinate Point::get_abscissa() const {
    return abscissa;
}

Point_coordinate Point::get_ordinate() const {
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


#endif //ALPHA_POINT_H
