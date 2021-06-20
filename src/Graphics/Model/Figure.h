#ifndef ALPHA_FIGURE_H
#define ALPHA_FIGURE_H

#include "Plots/Plot.h"
#include "Plots/Point.h"
#include "Plots/Segment.h"
#include "Plots/Polygon.h"

#include "Bounding_box.h"


namespace gr
{
class Figure
{
private:
    std::vector<Plot> plots;
    Bounding_box bounding_box;

public:
    Figure() = default;
    ~Figure() = default;

    Bounding_box get_bounding_box() const;
    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    void add_point(const Point& point);
    void add_segment(const Segment& segment);
    void add_polygon(const Polygon& polygon);
    void clear();

    unsigned nb_plots() const;
    const Plot& operator[](unsigned i) const;
};

Bounding_box Figure::get_bounding_box() const
{
    return bounding_box;
}

Coordinate Figure::get_min_abscissa() const
{
    return bounding_box.get_min_abscissa();
}

Coordinate Figure::get_max_abscissa() const
{
    return bounding_box.get_max_abscissa();
}

Coordinate Figure::get_min_ordinate() const
{
    return bounding_box.get_min_ordinate();
}

Coordinate Figure::get_max_ordinate() const
{
    return bounding_box.get_max_ordinate();
}

void Figure::add_point(const Point& point)
{
    Plot plot(point);
    plots.push_back(plot);
    bounding_box.extend(point);
}

void Figure::add_segment(const Segment& segment)
{
    plots.emplace_back(segment);
    bounding_box.extend(segment);
}

void Figure::add_polygon(const Polygon& polygon)
{
    plots.emplace_back(polygon);
    bounding_box.extend(polygon);
}

void Figure::clear()
{
    plots.clear();
    bounding_box.clear();
}

unsigned Figure::nb_plots() const
{
    return plots.size();
}

const Plot& Figure::operator[](unsigned int i) const
{
    return plots[i];
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
    figure.clear();
    std::string plot_name;
    Point point;
    Segment segment;
    Polygon polygon;

    while(!is.eof())
    {
        is >> plot_name;
        if(plot_name == POINT_NAME)
        {
            is >> point;
            figure.add_point(point);
        }
        else if(plot_name == SEGMENT_NAME)
        {
            is >> segment;
            figure.add_segment(segment);
        }
        else if(plot_name == POLYGON_NAME)
        {
            is >> polygon;
            figure.add_polygon(polygon);
        }
        plot_name = "";
    }
    return is;
}
}


#endif //ALPHA_FIGURE_H
