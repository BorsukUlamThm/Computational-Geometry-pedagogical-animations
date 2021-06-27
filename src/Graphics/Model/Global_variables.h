#ifndef ALPHA_GLOBAL_VARIABLES_H
#define ALPHA_GLOBAL_VARIABLES_H

#include <limits>


namespace gr
{
/// Some types for the objects coordinates
typedef float Coordinate;

#define MIN_COORDINATE std::numeric_limits<Coordinate>::min()
#define MAX_COORDINATE std::numeric_limits<Coordinate>::max()


/// Class names for serialization
#define POINT_NAME "Point"
#define SEGMENT_NAME "Segment"
#define POLYGON_NAME "Polygon"
#define CIRCLE_NAME "Circle"
#define LINE_NAME "Line"
#define TEXT_NAME "Text"


/// Colors
#define DEFAULT_BACKGROUND_COLOR sf::Color::White
#define DEFAULT_PLOT_COLOR sf::Color::Black


/// Fonts
#define DEFAULT_FONT "/home/felix/CLionProjects/Alpha/Fonts/arial.ttf"
#define ARIAL "/home/felix/CLionProjects/Alpha/Fonts/arial.ttf"
}

#endif //ALPHA_GLOBAL_VARIABLES_H
