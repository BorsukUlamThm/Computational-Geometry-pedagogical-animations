#ifndef ALPHA_TEXT_H
#define ALPHA_TEXT_H

#include <SFML/Graphics.hpp>
#include "../Global_variables.h"
#include "Point.h"
#include "Segment.h"


namespace gr
{
class Text
{
private:
    std::string content;
    Coordinate abscissa{};
    Coordinate ordinate{};
    unsigned size = 16;
    float offset_x = 0;
    float offset_y = 0;
    sf::Color color = DEFAULT_PLOT_COLOR;

public:
    Text() = default;
    Text(const std::string& text, const Coordinate& x, const Coordinate& y,
         unsigned size, float off_x, float off_y,
         const sf::Color& col = DEFAULT_PLOT_COLOR);
    Text(const std::string& text, const Point& point, unsigned size = 16,
         const sf::Color& col = DEFAULT_PLOT_COLOR);
    Text(const std::string& text, const Segment& segment, unsigned size = 16,
         const sf::Color& col = DEFAULT_PLOT_COLOR);
    Text(const Text& other);
    ~Text() = default;

    std::string get_content() const;
    Coordinate get_abscissa() const;
    Coordinate get_ordinate() const;
    unsigned get_size() const;
    float get_offset_x() const;
    float get_offset_y() const;
    sf::Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

//    friend std::istream& operator>>(std::istream&is, Text& text);
private:
    void aux_constructor(const std::string& text,
                         const Coordinate& x, const Coordinate& y,
                         unsigned size, float off_x, float off_y,
                         const sf::Color& col);
};

void Text::aux_constructor(const std::string& text,
                           const Coordinate& x, const Coordinate& y,
                           unsigned char_size, float off_x, float off_y,
                           const sf::Color& col)
{
    content = std::string(text);
    abscissa = Coordinate(x);
    ordinate = Coordinate(y);
    size = char_size;
    offset_x = off_x;
    offset_y = off_y;
    color = col;
}

Text::Text(const std::string& text, const Coordinate& x, const Coordinate& y,
           unsigned size, float off_x, float off_y, const sf::Color& col)
{
    aux_constructor(text, x, y, size, off_x, off_y, col);
}

Text::Text(const std::string& text, const Point& point, unsigned int size,
           const sf::Color& col)
{
    aux_constructor(text, point.get_abscissa(), point.get_ordinate(), size,
                    0, 3 + point.get_radius() + float(size) / 2, col);
}

Text::Text(const std::string& text, const Segment& segment, unsigned int size,
           const sf::Color& col)
{
    Coordinate x = (segment.get_origin().get_abscissa() +
            segment.get_destination().get_abscissa()) / 2;
    Coordinate y = (segment.get_origin().get_ordinate() +
                    segment.get_destination().get_ordinate()) / 2;
    aux_constructor(text, x, y, size,
                    0, 0, col);
}

Text::Text(const Text& other)
{
    content = std::string(other.content);
    abscissa = Coordinate(other.abscissa);
    ordinate = Coordinate(other.ordinate);
    size = other.size;
    offset_x = other.offset_x;
    offset_y = other.offset_y;
    color = other.color;
}

std::string Text::get_content() const
{
    return content;
}

Coordinate Text::get_abscissa() const
{
    return abscissa;
}

Coordinate Text::get_ordinate() const
{
    return ordinate;
}

unsigned Text::get_size() const
{
    return size;
}

float Text::get_offset_x() const
{
    return offset_x;
}

float Text::get_offset_y() const
{
    return offset_y;
}

sf::Color Text::get_color() const
{
    return color;
}

Coordinate Text::get_min_abscissa() const
{
    return abscissa;
}

Coordinate Text::get_max_abscissa() const
{
    return abscissa;
}

Coordinate Text::get_min_ordinate() const
{
    return ordinate;
}

Coordinate Text::get_max_ordinate() const
{
    return ordinate;
}
}


#endif //ALPHA_TEXT_H
