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
#define DARK_GREY (sf::Color(33, 47, 60))
#define LIGHT_GREY (sf::Color(208, 211, 212))

#define RED (sf::Color(203, 67, 53))
#define PURPLE (sf::Color(175, 122, 197))
#define BLUE (sf::Color(52, 152, 219))
#define GREEN (sf::Color(39, 174, 96))
#define YELLOW (sf::Color(241, 196, 15))

#define DEFAULT_BACKGROUND_COLOR DARK_GREY
#define DEFAULT_PLOT_COLOR LIGHT_GREY


/// Fonts
constexpr char ARIAL[] = "/home/felix/CLionProjects/Alpha/Fonts/arial.ttf";
#define DEFAULT_FONT ARIAL
}

#endif //ALPHA_GLOBAL_VARIABLES_H
