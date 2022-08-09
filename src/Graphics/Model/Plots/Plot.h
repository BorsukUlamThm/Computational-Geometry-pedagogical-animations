#pragma once

/** @cond */
#include <iostream>
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Polygon_plt.h"
#include "Circle_plt.h"
#include "Line_plt.h"
#include "Text_plt.h"


namespace gr
{

enum Plot_type
{
    POINT_PLT,
    SEGMENT_PLT,
    VECTOR_PLT,
    POLYGON_PLT,
    CIRCLE_PLT,
    LINE_PLT,
    TEXT_PLT
};

class Plot
{
private:
    Plot_type plot_type;
    union
    {
        Point_plt u_point;
        Segment_plt u_segment;
        Vector_plt u_vector;
        Polygon_plt u_polygon;
        Circle_plt u_circle;
        Line_plt u_line;
        Text_plt u_text;
    };

public:
    explicit Plot(Plot_type type);
    explicit Plot(const Point_plt& point);
    explicit Plot(const Segment_plt& segment);
    explicit Plot(const Vector_plt& vector);
    explicit Plot(const Polygon_plt& polygon);
    explicit Plot(const Circle_plt& circle);
    explicit Plot(const Line_plt& line);
    explicit Plot(const Text_plt& text);
    Plot(const Plot& other);
    ~Plot();

    Plot_type type() const;
    Point_plt point() const;
    Segment_plt segment() const;
    Vector_plt vector() const;
    Polygon_plt polygon() const;
    Circle_plt circle() const;
    Line_plt line() const;
    Text_plt text() const;

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
        case POINT_PLT:
            new (&u_point) Point_plt();
            break;
        case SEGMENT_PLT:
            new (&u_segment) Segment_plt();
            break;
        case VECTOR_PLT:
            new (&u_vector) Vector_plt();
            break;
        case POLYGON_PLT:
            new (&u_polygon) Polygon_plt();
            break;
        case CIRCLE_PLT:
            new (&u_circle) Circle_plt();
            break;
        case LINE_PLT:
            new (&u_line) Line_plt();
            break;
        case TEXT_PLT:
            new (&u_text) Text_plt();
            break;
    }
}

Plot::Plot(const Point_plt& point):
    plot_type(POINT_PLT),
    u_point(Point_plt(point))
{}

Plot::Plot(const Segment_plt& segment):
    plot_type(SEGMENT_PLT),
    u_segment(Segment_plt(segment))
{}

Plot::Plot(const Vector_plt& vector):
    plot_type(VECTOR_PLT),
    u_vector(Vector_plt(vector))
{}

Plot::Plot(const Polygon_plt& polygon):
    plot_type(POLYGON_PLT),
    u_polygon(Polygon_plt(polygon))
{}

Plot::Plot(const Circle_plt& circle):
    plot_type(CIRCLE_PLT),
    u_circle(Circle_plt(circle))
{}

Plot::Plot(const Line_plt& line):
    plot_type(LINE_PLT),
    u_line(Line_plt(line))
{}

Plot::Plot(const Text_plt& text):
    plot_type(TEXT_PLT),
    u_text(Text_plt(text))
{}

Plot::Plot(const Plot& other)
{
    plot_type = other.plot_type;
    switch(plot_type)
    {
        case POINT_PLT:
            new (&u_point) Point_plt(other.u_point);
            break;
        case SEGMENT_PLT:
            new (&u_segment) Segment_plt(other.u_segment);
            break;
        case VECTOR_PLT:
            new (&u_vector) Vector_plt(other.u_vector);
            break;
        case POLYGON_PLT:
            new (&u_polygon) Polygon_plt(other.u_polygon);
            break;
        case CIRCLE_PLT:
            new (&u_circle) Circle_plt(other.u_circle);
            break;
        case LINE_PLT:
            new (&u_line) Line_plt(other.u_line);
            break;
        case TEXT_PLT:
            new (&u_text) Text_plt(other.u_text);
            break;
    }
}

Plot::~Plot()
{
    switch(plot_type)
    {
        case POINT_PLT:
            u_point.~Point_plt();
            break;
        case SEGMENT_PLT:
            u_segment.~Segment_plt();
            break;
        case VECTOR_PLT:
            u_vector.~Vector_plt();
            break;
        case POLYGON_PLT:
            u_polygon.~Polygon_plt();
            break;
        case CIRCLE_PLT:
            u_circle.~Circle_plt();
            break;
        case LINE_PLT:
            u_line.~Line_plt();
            break;
        case TEXT_PLT:
            u_text.~Text_plt();
            break;
    }
}

Plot_type Plot::type() const
{
    return plot_type;
}

Point_plt Plot::point() const
{
    return u_point;
}

Segment_plt Plot::segment() const
{
    return u_segment;
}

Vector_plt Plot::vector() const
{
    return u_vector;
}

Polygon_plt Plot::polygon() const
{
    return u_polygon;
}

Circle_plt Plot::circle() const
{
    return u_circle;
}

Line_plt Plot::line() const
{
    return u_line;
}

Text_plt Plot::text() const
{
    return u_text;
}

Coordinate Plot::get_min_abscissa() const
{
    switch(plot_type)
    {
        case POINT_PLT:
            return u_point.get_min_abscissa();
        case SEGMENT_PLT:
            return u_segment.get_min_abscissa();
            case VECTOR_PLT:
                return u_vector.get_min_abscissa();
        case POLYGON_PLT:
            return u_polygon.get_min_abscissa();
        case CIRCLE_PLT:
            return u_circle.get_min_abscissa();
        case LINE_PLT:
            return u_line.get_min_abscissa();
        case TEXT_PLT:
            return u_text.get_min_abscissa();
    }
    return 0;
}

Coordinate Plot::get_max_abscissa() const
{
    switch(plot_type)
    {
        case POINT_PLT:
            return u_point.get_max_abscissa();
        case SEGMENT_PLT:
            return u_segment.get_max_abscissa();
            case VECTOR_PLT:
                return u_vector.get_max_abscissa();
        case POLYGON_PLT:
            return u_polygon.get_max_abscissa();
        case CIRCLE_PLT:
            return u_circle.get_max_abscissa();
        case LINE_PLT:
            return u_line.get_max_abscissa();
        case TEXT_PLT:
            return u_text.get_max_abscissa();
    }
    return 0;
}

Coordinate Plot::get_min_ordinate() const
{
    switch(plot_type)
    {
        case POINT_PLT:
            return u_point.get_min_ordinate();
        case SEGMENT_PLT:
            return u_segment.get_min_ordinate();
            case VECTOR_PLT:
                return u_vector.get_min_ordinate();
        case POLYGON_PLT:
            return u_polygon.get_min_ordinate();
        case CIRCLE_PLT:
            return u_circle.get_min_ordinate();
        case LINE_PLT:
            return u_line.get_min_ordinate();
        case TEXT_PLT:
            return u_text.get_min_ordinate();
    }
    return 0;
}

Coordinate Plot::get_max_ordinate() const
{
    switch(plot_type)
    {
        case POINT_PLT:
            return u_point.get_max_ordinate();
        case SEGMENT_PLT:
            return u_segment.get_max_ordinate();
        case VECTOR_PLT:
            return u_vector.get_max_ordinate();
        case POLYGON_PLT:
            return u_polygon.get_max_ordinate();
        case CIRCLE_PLT:
            return u_circle.get_max_ordinate();
        case LINE_PLT:
            return u_line.get_max_ordinate();
        case TEXT_PLT:
            return u_text.get_max_ordinate();
    }
    return 0;
}

}
