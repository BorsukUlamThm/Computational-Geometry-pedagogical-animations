#ifndef ALPHA_PLOT_H
#define ALPHA_PLOT_H

#include "Global_variables.h"
#include <iostream>


namespace gr
{
class Plot
{
public:
    Plot() = default;

    virtual ~Plot() = default;

    virtual Coordinate get_min_abscissa() const = 0;

    virtual Coordinate get_max_abscissa() const = 0;

    virtual Coordinate get_min_ordinate() const = 0;

    virtual Coordinate get_max_ordinate() const = 0;
};
}


#endif //ALPHA_PLOT_H
