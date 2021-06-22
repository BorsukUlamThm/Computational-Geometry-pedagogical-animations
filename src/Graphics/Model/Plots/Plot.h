#ifndef ALPHA_PLOT_H
#define ALPHA_PLOT_H

#include "../Global_variables.h"
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Point.h"
#include "Segment.h"
#include "Polygon.h"
#include "Circle.h"
#include "Line.h"


namespace gr
{

enum Plot_type {POINT, SEGMENT, POLYGON, CIRCLE, LINE};

union Plot_value
{
    Point point;
    Segment segment;
    Polygon polygon;
    Circle circle;
    Line line;

    Plot_value(){};
    ~Plot_value(){};
};

class Plot
{
private:
    Plot_type plot_type;
    Plot_value plot_value;

public:
    Plot() = default;
    Plot(const Point& point);
    Plot(const Segment& segment);
    Plot(const Polygon& polygon);
    Plot(const Circle& circle);
    Plot(const Line& line);
    Plot(const Plot& other);

    Plot_type type() const;
    Point point() const;
    Segment segment() const;
    Polygon polygon() const;
    Circle circle() const;
    Line line() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;
};

Plot::Plot(const Point& point)
{
    plot_type = POINT;
    plot_value.point = Point(point);
}

Plot::Plot(const Segment& segment)
{
    plot_type = SEGMENT;
    plot_value.segment = Segment(segment);
}

Plot::Plot(const Polygon& polygon)
{
    plot_type = POLYGON;
    plot_value.polygon = Polygon(polygon);
}

Plot::Plot(const Circle& circle)
{
    plot_type = CIRCLE;
    plot_value.circle = Circle(circle);
}

Plot::Plot(const Line& line)
{
    plot_type = LINE;
    plot_value.line = Line(line);
}

Plot::Plot(const Plot& other)
{
    plot_type = other.plot_type;
    switch(plot_type)
    {
        case POINT:
            plot_value.point = other.plot_value.point;
            break;
        case SEGMENT:
            plot_value.segment = other.plot_value.segment;
            break;
        case POLYGON:
            plot_value.polygon = other.plot_value.polygon;
            break;
        case CIRCLE:
            plot_value.circle = other.plot_value.circle;
            break;
        case LINE:
            plot_value.line = other.plot_value.line;
            break;
    }
}

Plot_type Plot::type() const
{
    return plot_type;
}

Point Plot::point() const
{
    return plot_value.point;
}

Segment Plot::segment() const
{
    return plot_value.segment;
}

Polygon Plot::polygon() const
{
    return plot_value.polygon;
}

Circle Plot::circle() const
{
    return plot_value.circle;
}

Line Plot::line() const
{
    return plot_value.line;
}

Coordinate Plot::get_min_abscissa() const
{
    switch(plot_type)
    {
        case POINT:
            return plot_value.point.get_min_abscissa();
        case SEGMENT:
            return plot_value.segment.get_min_abscissa();
        case POLYGON:
            return plot_value.polygon.get_min_abscissa();
        case CIRCLE:
            return plot_value.circle.get_min_abscissa();
        case LINE:
            return plot_value.line.get_min_abscissa();
    }
    return 0;
}

Coordinate Plot::get_max_abscissa() const
{
    switch(plot_type)
    {
        case POINT:
            return plot_value.point.get_max_abscissa();
        case SEGMENT:
            return plot_value.segment.get_max_abscissa();
        case POLYGON:
            return plot_value.polygon.get_max_abscissa();
        case CIRCLE:
            return plot_value.circle.get_max_abscissa();
        case LINE:
            return plot_value.line.get_max_abscissa();
    }
    return 0;
}

Coordinate Plot::get_min_ordinate() const
{
    switch(plot_type)
    {
        case POINT:
            return plot_value.point.get_min_ordinate();
        case SEGMENT:
            return plot_value.segment.get_min_ordinate();
        case POLYGON:
            return plot_value.polygon.get_min_ordinate();
        case CIRCLE:
            return plot_value.circle.get_min_ordinate();
        case LINE:
            return plot_value.line.get_min_ordinate();
    }
    return 0;
}

Coordinate Plot::get_max_ordinate() const
{
    switch(plot_type)
    {
        case POINT:
            return plot_value.point.get_max_ordinate();
        case SEGMENT:
            return plot_value.segment.get_max_ordinate();
        case POLYGON:
            return plot_value.polygon.get_max_ordinate();
        case CIRCLE:
            return plot_value.circle.get_max_ordinate();
        case LINE:
            return plot_value.line.get_max_ordinate();
    }
    return 0;
}

}


#endif //ALPHA_PLOT_H
