#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Segment_plt.h"

namespace gr
{
class Line_plt
{
private:
    // line equation : ax + by + c = 0
    Coordinate a{};
    Coordinate b{};
    Coordinate c{};
    Color color = DEFAULT_PLOT_COLOR;

public:
    Line_plt() = default;
    Line_plt(const Coordinate& a, const Coordinate& b, const Coordinate& c,
         Color col = DEFAULT_PLOT_COLOR);
    Line_plt(const Segment_plt& segment, Color col = DEFAULT_PLOT_COLOR);
    Line_plt(const Point_plt& point1, const Point_plt& point2,
         Color col = DEFAULT_PLOT_COLOR);
    Line_plt(const Coordinate& x1, const Coordinate& y1,
         const Coordinate& x2, const Coordinate& y2,
         Color col = DEFAULT_PLOT_COLOR);
    Line_plt(const Line_plt& other);
    ~Line_plt() = default;

    Coordinate get_a() const;
    Coordinate get_b() const;
    Coordinate get_c() const;
    Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream&is, Line_plt& line);

private:
    void aux_constructor(const Coordinate& x1, const Coordinate& y1,
                         const Coordinate& x2, const Coordinate& y2,
                         Color col);
};

Line_plt::Line_plt(const Coordinate& a, const Coordinate& b, const Coordinate& c,
           Color col)
{
    this-> a = Coordinate(a);
    this-> b = Coordinate(b);
    this-> c = Coordinate(c);
    color = col;
}

void Line_plt::aux_constructor(const Coordinate& x1, const Coordinate& y1,
                           const Coordinate& x2, const Coordinate& y2,
                           Color col)
{
    a = y2 - y1;
    b = x1 - x2;
    c = - a * x1 - b * y1;
    color = col;
}

Line_plt::Line_plt(const Segment_plt& segment, Color col)
{
    Coordinate x1 = segment.get_origin().get_abscissa();
    Coordinate y1 = segment.get_origin().get_ordinate();
    Coordinate x2 = segment.get_destination().get_abscissa();
    Coordinate y2 = segment.get_destination().get_ordinate();
    aux_constructor(x1, y1, x2, y2, col);
}

Line_plt::Line_plt(const Point_plt& point1, const Point_plt& point2, Color col)
{
    Coordinate x1 = point1.get_abscissa();
    Coordinate y1 = point1.get_ordinate();
    Coordinate x2 = point2.get_abscissa();
    Coordinate y2 = point2.get_ordinate();
    aux_constructor(x1, y1, x2, y2, col);
}

Line_plt::Line_plt(const Coordinate& x1, const Coordinate& y1,
           const Coordinate& x2, const Coordinate& y2,
           Color col)
{
    aux_constructor(x1, y1, x2, y2, col);
}

Line_plt::Line_plt(const Line_plt& other)
{
    a = Coordinate(other.a);
    b = Coordinate(other.b);
    c = Coordinate(other.c);
    color = other.color;
}

Coordinate Line_plt::get_a() const
{
    return a;
}

Coordinate Line_plt::get_b() const
{
    return b;
}

Coordinate Line_plt::get_c() const
{
    return c;
}

Color Line_plt::get_color() const
{
    return color;
}

Coordinate Line_plt::get_min_abscissa() const
{
    return MAX_COORDINATE;
}

Coordinate Line_plt::get_max_abscissa() const
{
    return MIN_COORDINATE;
}

Coordinate Line_plt::get_min_ordinate() const
{
    return MAX_COORDINATE;
}

Coordinate Line_plt::get_max_ordinate() const
{
    return MIN_COORDINATE;
}

std::ostream& operator<<(std::ostream& os, const Line_plt& line)
{
    os << LINE_NAME << " " << line.get_a()
                    << " " << line.get_b()
                    << " " << line.get_c();
    return os;
}

std::istream& operator>>(std::istream& is, Line_plt& line)
{
    is >> line.a >> line.b >> line.c;
    return is;
}
}