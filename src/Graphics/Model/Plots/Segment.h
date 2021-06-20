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

public:
    Segment() = default;
    Segment(const Point& ogn, const Point& dst);
    Segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
            const Coordinate& dst_x, const Coordinate& dst_y);
    Segment(const Segment& other);

    Point get_origin() const;
    Point get_destination() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Segment& segment);
};

Segment::Segment(const Point& ogn, const Point& dst)
{
    origin = Point(ogn);
    destination = Point(dst);
}

Segment::Segment(const Coordinate& ogn_x, const Coordinate& ogn_y,
                 const Coordinate& dst_x, const Coordinate& dst_y)
{
    origin = Point(ogn_x, ogn_y);
    destination = Point(dst_x, dst_y);
}

Segment::Segment(const Segment& other) {
    origin = Point(other.get_origin());
    destination = Point(other.get_destination());
}

Point Segment::get_origin() const {
    return origin;
}

Point Segment::get_destination() const {
    return destination;
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
