#ifndef ALPHA_POINT_ACQ_H
#define ALPHA_POINT_ACQ_H

#include <SFML/Graphics.hpp>
#include "Graphics/Model/Global_variables.h"


namespace gr
{
class Point_acq
{
private:
    Color color = DEFAULT_PLOT_COLOR;
    float radius = 3;

public:
    Point_acq() = default;
    explicit Point_acq(Color col, float rad = 3);
    Point_acq(const Point_acq& other);
    ~Point_acq() = default;

    Color get_color() const;
    float get_radius() const;
};

Point_acq::Point_acq(Color col, float rad)
{
    color = col;
    radius = rad;
}

Point_acq::Point_acq(const Point_acq& other)
{
    color = other.color;
    radius = other.radius;
}

Color Point_acq::get_color() const
{
    return color;
}

float Point_acq::get_radius() const
{
    return radius;
}
}


#endif //ALPHA_POINT_ACQ_H
