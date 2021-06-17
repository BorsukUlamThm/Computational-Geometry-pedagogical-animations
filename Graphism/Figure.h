#ifndef ALPHA_FIGURE_H
#define ALPHA_FIGURE_H

#include "Model/Plot.h"
#include "Model/Point.h"
#include "Model/Segment.h"
#include "Model/Polygon.h"

#include "Bounding_box.h"


namespace gr
{
class Figure
{
public:
    std::vector<Plot*> plots;
    Bounding_box bounding_box;

public:
    Figure() = default;
    explicit Figure(const std::string& file_path);
    ~Figure();

    void add_point(const Point& point);
    void add_segment(const Segment& segment);
    void add_polygon(const Polygon& polygon);

};

Figure::Figure(const std::string& file_path)
{
    std::ifstream is(file_path);
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
            add_point(point);
        }
        else if(plot_name == SEGMENT_NAME)
        {
            is >> segment;
            add_segment(segment);
        }
        else if(plot_name == POLYGON_NAME)
        {
            is >> polygon;
            add_polygon(polygon);
        }
        plot_name = "";
    }
}

Figure::~Figure()
{
    for(auto& plot : plots)
    {
        delete plot;
    }
}

void Figure::add_point(const Point& point)
{
    Point* new_point = new Point(point);
    plots.push_back(new_point);
    bounding_box.extend(point);
}

void Figure::add_segment(const Segment& segment)
{
    Segment* new_segment = new Segment(segment);
    plots.push_back(new_segment);
    bounding_box.extend(segment);
}

void Figure::add_polygon(const Polygon& polygon)
{
    Polygon* new_polygon = new Polygon(polygon);
    plots.push_back(new_polygon);
    bounding_box.extend(polygon);
}
}


#endif //ALPHA_FIGURE_H
