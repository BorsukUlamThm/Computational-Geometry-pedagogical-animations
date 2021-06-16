#ifndef ALPHA_SEGMENT_H
#define ALPHA_SEGMENT_H

#include "Point.h"

class Segment : public Plot
{
private:
    Point origin;
    Point destination;

public:
    Segment() = default;
    Segment(const Point& ogn, const Point& dst);
    Segment(const Point_coordinate& ogn_x, const Point_coordinate& ogn_y,
            const Point_coordinate& dst_x, const Point_coordinate& dst_y);
    Segment(const Segment& other);

    Point get_origin() const;
    Point get_destination() const;

    friend std::istream& operator>>(std::istream& is, Segment& segment);
};

Segment::Segment(const Point& ogn, const Point& dst)
{
    origin = Point(ogn);
    destination = Point(dst);
}

Segment::Segment(const Point_coordinate& ogn_x, const Point_coordinate& ogn_y,
                 const Point_coordinate& dst_x, const Point_coordinate& dst_y)
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


#endif //ALPHA_SEGMENT_H
