#ifndef ALPHA_PLOT_H
#define ALPHA_PLOT_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Graphics/Model/Global_variables.h"

#include "Point.h"
#include "Segment.h"
#include "Vector.h"
#include "Polygon.h"
#include "Circle.h"
#include "Line.h"
#include "Text.h"

// doc for union https://docs.microsoft.com/en-us/cpp/cpp/unions?view=msvc-160


namespace gr
{

enum Plot_type {POINT, SEGMENT, VECTOR, POLYGON, CIRCLE, LINE, TEXT};

class Plot
{
private:
    Plot_type plot_type;
    union
    {
        Point u_point;
        Segment u_segment;
        Vector u_vector;
        Polygon u_polygon;
        Circle u_circle;
        Line u_line;
        Text u_text;
    };

public:
    explicit Plot(Plot_type type);
    explicit Plot(const Point& point);
    explicit Plot(const Segment& segment);
    explicit Plot(const Vector& vector);
    explicit Plot(const Polygon& polygon);
    explicit Plot(const Circle& circle);
    explicit Plot(const Line& line);
    explicit Plot(const Text& text);
    Plot(const Plot& other);
    ~Plot();

    Plot_type type() const;
    Point point() const;
    Segment segment() const;
    Vector vector() const;
    Polygon polygon() const;
    Circle circle() const;
    Line line() const;
    Text text() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;
};

Plot::Plot(Plot_type type)
{
    plot_type = type;
    switch(type)
    {
        case POINT:
            new (&u_point) Point();
            break;
        case SEGMENT:
            new (&u_segment) Segment();
            break;
        case VECTOR:
            new (&u_vector) Vector();
            break;
        case POLYGON:
            new (&u_polygon) Polygon();
            break;
        case CIRCLE:
            new (&u_circle) Circle();
            break;
        case LINE:
            new (&u_line) Line();
            break;
        case TEXT:
            new (&u_text) Text();
            break;
    }
}

Plot::Plot(const Point& point):
    plot_type(POINT),
    u_point(Point(point))
{}

Plot::Plot(const Segment& segment):
    plot_type(SEGMENT),
    u_segment(Segment(segment))
{}

Plot::Plot(const Vector& vector):
    plot_type(VECTOR),
    u_vector(Vector(vector))
{}

Plot::Plot(const Polygon& polygon):
    plot_type(POLYGON),
    u_polygon(Polygon(polygon))
{}

Plot::Plot(const Circle& circle):
    plot_type(CIRCLE),
    u_circle(Circle(circle))
{}

Plot::Plot(const Line& line):
    plot_type(LINE),
    u_line(Line(line))
{}

Plot::Plot(const Text& text):
    plot_type(TEXT),
    u_text(Text(text))
{}

Plot::Plot(const Plot& other)
{
    plot_type = other.plot_type;
    switch(plot_type)
    {
        case POINT:
            new (&u_point) Point(other.u_point);
            break;
        case SEGMENT:
            new (&u_segment) Segment(other.u_segment);
            break;
        case VECTOR:
            new (&u_vector) Vector(other.u_vector);
            break;
        case POLYGON:
            new (&u_polygon) Polygon(other.u_polygon);
            break;
        case CIRCLE:
            new (&u_circle) Circle(other.u_circle);
            break;
        case LINE:
            new (&u_line) Line(other.u_line);
            break;
        case TEXT:
            new (&u_text) Text(other.u_text);
            break;
    }
}

Plot::~Plot()
{
    switch(plot_type)
    {
        case POINT:
            u_point.~Point();
            break;
        case SEGMENT:
            u_segment.~Segment();
            break;
        case VECTOR:
            u_vector.~Vector();
            break;
        case POLYGON:
            u_polygon.~Polygon();
            break;
        case CIRCLE:
            u_circle.~Circle();
            break;
        case LINE:
            u_line.~Line();
            break;
        case TEXT:
            u_text.~Text();
            break;
    }
}

Plot_type Plot::type() const
{
    return plot_type;
}

Point Plot::point() const
{
    return u_point;
}

Segment Plot::segment() const
{
    return u_segment;
}

Vector Plot::vector() const
{
    return u_vector;
}

Polygon Plot::polygon() const
{
    return u_polygon;
}

Circle Plot::circle() const
{
    return u_circle;
}

Line Plot::line() const
{
    return u_line;
}

Text Plot::text() const
{
    return u_text;
}

Coordinate Plot::get_min_abscissa() const
{
    switch(plot_type)
    {
        case POINT:
            return u_point.get_min_abscissa();
        case SEGMENT:
            return u_segment.get_min_abscissa();
            case VECTOR:
                return u_vector.get_min_abscissa();
        case POLYGON:
            return u_polygon.get_min_abscissa();
        case CIRCLE:
            return u_circle.get_min_abscissa();
        case LINE:
            return u_line.get_min_abscissa();
        case TEXT:
            return u_text.get_min_abscissa();
    }
    return 0;
}

Coordinate Plot::get_max_abscissa() const
{
    switch(plot_type)
    {
        case POINT:
            return u_point.get_max_abscissa();
        case SEGMENT:
            return u_segment.get_max_abscissa();
            case VECTOR:
                return u_vector.get_max_abscissa();
        case POLYGON:
            return u_polygon.get_max_abscissa();
        case CIRCLE:
            return u_circle.get_max_abscissa();
        case LINE:
            return u_line.get_max_abscissa();
        case TEXT:
            return u_text.get_max_abscissa();
    }
    return 0;
}

Coordinate Plot::get_min_ordinate() const
{
    switch(plot_type)
    {
        case POINT:
            return u_point.get_min_ordinate();
        case SEGMENT:
            return u_segment.get_min_ordinate();
            case VECTOR:
                return u_vector.get_min_ordinate();
        case POLYGON:
            return u_polygon.get_min_ordinate();
        case CIRCLE:
            return u_circle.get_min_ordinate();
        case LINE:
            return u_line.get_min_ordinate();
        case TEXT:
            return u_text.get_min_ordinate();
    }
    return 0;
}

Coordinate Plot::get_max_ordinate() const
{
    switch(plot_type)
    {
        case POINT:
            return u_point.get_max_ordinate();
        case SEGMENT:
            return u_segment.get_max_ordinate();
        case VECTOR:
            return u_vector.get_max_ordinate();
        case POLYGON:
            return u_polygon.get_max_ordinate();
        case CIRCLE:
            return u_circle.get_max_ordinate();
        case LINE:
            return u_line.get_max_ordinate();
        case TEXT:
            return u_text.get_max_ordinate();
    }
    return 0;
}

}


#endif //ALPHA_PLOT_H
