#ifndef ALPHA_GLOBAL_VARIABLES_H
#define ALPHA_GLOBAL_VARIABLES_H

#include <limits>


namespace gr
{
/// Some types for the objects coordinates
typedef double Coordinate;

#define MIN_COORDINATE std::numeric_limits<double>::min()
#define MAX_COORDINATE std::numeric_limits<double>::max()


/// Class names for serialization
#define POINT_NAME "Point"
#define SEGMENT_NAME "Segment"
#define POLYGON_NAME "Polygon"
}

#endif //ALPHA_GLOBAL_VARIABLES_H
