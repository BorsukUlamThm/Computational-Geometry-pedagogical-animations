#ifndef ALPHA_BOUNDING_BOX_H
#define ALPHA_BOUNDING_BOX_H

#include "Model/Point.h"
#include "Model/Segment.h"
#include "Model/Polygon.h"


namespace gr
{
class Bounding_box
{
private:
    Coordinate min_abscissa = MAX_COORDINATE;
    Coordinate max_abscissa = MIN_COORDINATE;
    Coordinate min_ordinate = MAX_COORDINATE;
    Coordinate max_ordinate = MIN_COORDINATE;

public:
    Bounding_box() = default;
    Bounding_box(const Bounding_box& other);

    void extend(const Plot& plot);

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;
};

Bounding_box::Bounding_box(const Bounding_box& other)
{
    min_abscissa = Coordinate(other.min_abscissa);
    max_abscissa = Coordinate(other.max_abscissa);
    min_ordinate = Coordinate(other.min_ordinate);
    max_ordinate = Coordinate(other.max_ordinate);
}

void Bounding_box::extend(const Plot& plot)
{
    min_abscissa = std::min(min_abscissa, plot.get_min_abscissa());
    max_abscissa = std::max(max_abscissa, plot.get_max_abscissa());
    min_ordinate = std::min(min_ordinate, plot.get_min_ordinate());
    max_ordinate = std::max(max_ordinate, plot.get_max_ordinate());
}

Coordinate Bounding_box::get_min_abscissa() const
{
    return min_abscissa;
}

Coordinate Bounding_box::get_max_abscissa() const
{
    return max_abscissa;
}

Coordinate Bounding_box::get_min_ordinate() const
{
    return min_ordinate;
}

Coordinate Bounding_box::get_max_ordinate() const
{
    return max_ordinate;
}
}


#endif //ALPHA_BOUNDING_BOX_H
