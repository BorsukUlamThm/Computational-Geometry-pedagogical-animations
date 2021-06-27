#ifndef ALPHA_SEGMENT_H
#define ALPHA_SEGMENT_H

#include "Point.h"


namespace gr
{
class Segment
{
private:
    Point origin;
    Point destination;
    sf::Color line_color = DEFAULT_PLOT_COLOR;

public:
    Segment() = default;
    Segment(const Point& ogn, const Point& dst,
            const sf::Color& line_col = DEFAULT_PLOT_COLOR);
    Segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
            const Coordinate& dst_x, const Coordinate& dst_y,
            const sf::Color& line_col = DEFAULT_PLOT_COLOR,
            const sf::Color& end_points_col = DEFAULT_PLOT_COLOR);
    Segment(const Segment& other);
    ~Segment() = default;

    Point get_origin() const;
    Point get_destination() const;
    sf::Color get_line_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Segment& segment);
};

Segment::Segment(const Point& ogn, const Point& dst,
                 const sf::Color& line_col)
{
    origin = Point(ogn);
    destination = Point(dst);
    line_color = line_col;
}

Segment::Segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
                 const Coordinate& dst_x, const Coordinate& dst_y,
                 const sf::Color& line_col, const sf::Color& end_points_col)
{
    origin = Point(ogn_x, ogn_y, end_points_col);
    destination = Point(dst_x, dst_y, end_points_col);
    line_color = line_col;
}

Segment::Segment(const Segment& other)
{
    origin = Point(other.origin);
    destination = Point(other.destination);
    line_color = other.line_color;
}

Point Segment::get_origin() const
{
    return origin;
}

Point Segment::get_destination() const
{
    return destination;
}

sf::Color Segment::get_line_color() const
{
    return line_color;
}

Coordinate Segment::get_min_abscissa() const
{
    return std::min(origin.get_min_abscissa(),
                    destination.get_min_abscissa());
}

Coordinate Segment::get_max_abscissa() const
{
    return std::max(origin.get_max_abscissa(),
                    destination.get_max_abscissa());
}

Coordinate Segment::get_min_ordinate() const
{
    return std::min(origin.get_min_ordinate(),
                    destination.get_min_ordinate());
}

Coordinate Segment::get_max_ordinate() const
{
    return std::max(origin.get_max_ordinate(),
                    destination.get_max_ordinate());
}

std::ostream& operator<<(std::ostream& os, const Segment& segment)
{
    os << SEGMENT_NAME << " " << segment.get_origin()
                       << " " << segment.get_destination();
    return os;
}

std::istream& operator>>(std::istream& is, Segment& segment)
{
    std::string dummy;
    is >> dummy;
    is >> segment.origin;
    is >> dummy;
    is >> segment.destination;
    return is;
}
}


#endif //ALPHA_SEGMENT_H
