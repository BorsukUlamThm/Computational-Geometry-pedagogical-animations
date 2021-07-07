#ifndef ALPHA_GLOBAL_VARIABLES_H
#define ALPHA_GLOBAL_VARIABLES_H

#include <limits>
#include <string>


namespace gr
{
/// Some types for the objects coordinates
typedef float Coordinate;

constexpr Coordinate MIN_COORDINATE = std::numeric_limits<Coordinate>::lowest();
constexpr Coordinate MAX_COORDINATE = std::numeric_limits<Coordinate>::max();


/// Class names for serialization
constexpr char POINT_NAME[] = "Point";
constexpr char SEGMENT_NAME[] = "Segment";
constexpr char VECTOR_NAME[] = "Vector";
constexpr char POLYGON_NAME[] = "Polygon";
constexpr char CIRCLE_NAME[] = "Circle";
constexpr char LINE_NAME[] = "Line";
constexpr char TEXT_NAME[] = "Text";


/// Colors
#define DEFAULT_BACKGROUND_COLOR sf::Color::White
#define DEFAULT_PLOT_COLOR sf::Color::Black


/// Fonts
constexpr char ARIAL[] = "/home/felix/CLionProjects/Alpha/Fonts/arial.ttf";
#define DEFAULT_FONT ARIAL
}

#endif //ALPHA_GLOBAL_VARIABLES_H
