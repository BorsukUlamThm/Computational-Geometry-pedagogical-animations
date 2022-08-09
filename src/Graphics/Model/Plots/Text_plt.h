#pragma once

/** @cond */
#include <SFML/Graphics.hpp>
/** @endcond */
#include "Vector_plt.h"


namespace gr
{
class Text_plt
{
private:
    std::string content{};
    Coordinate abscissa{};
    Coordinate ordinate{};
    unsigned size = 16;
    float offset_x = 0;
    float offset_y = 0;
    Color color = DEFAULT_PLOT_COLOR;

public:
    Text_plt() = default;
    Text_plt(const std::string& text, const Coordinate& x, const Coordinate& y,
         unsigned size = 16, float off_x = 0, float off_y = 0,
         const Color col = DEFAULT_PLOT_COLOR);
    Text_plt(const std::string& text, const Point_plt& point, unsigned size = 16,
         const Color col = DEFAULT_PLOT_COLOR);
    Text_plt(const std::string& text, const Segment_plt& segment, unsigned size = 16,
         const Color col = DEFAULT_PLOT_COLOR);
    Text_plt(const std::string& text, const Vector_plt& vector, unsigned size = 16,
         const Color col = DEFAULT_PLOT_COLOR);
    Text_plt(const Text_plt& other);
    ~Text_plt() = default;

    std::string get_content() const;
    Coordinate get_abscissa() const;
    Coordinate get_ordinate() const;
    unsigned get_size() const;
    float get_offset_x() const;
    float get_offset_y() const;
    Color get_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

//    friend std::istream& operator>>(std::istream&is, Text& text);
private:
    void aux_constructor(const std::string& text,
                         const Coordinate& x, const Coordinate& y,
                         unsigned size, float off_x, float off_y,
                         Color col);
};

void Text_plt::aux_constructor(const std::string& text,
                           const Coordinate& x, const Coordinate& y,
                           unsigned char_size, float off_x, float off_y,
                           Color col)
{
    content = std::string(text);
    abscissa = Coordinate(x);
    ordinate = Coordinate(y);
    size = char_size;
    offset_x = off_x;
    offset_y = off_y;
    color = col;
}

Text_plt::Text_plt(const std::string& text, const Coordinate& x, const Coordinate& y,
           unsigned size, float off_x, float off_y, Color col)
{
    aux_constructor(text, x, y, size, off_x, off_y, col);
}

Text_plt::Text_plt(const std::string& text, const Point_plt& point, unsigned int size,
           Color col)
{
    aux_constructor(text, point.get_abscissa(), point.get_ordinate(), size,
                    0, 3 + point.get_radius() + float(size) / 2, col);
}

Text_plt::Text_plt(const std::string& text, const Segment_plt& segment, unsigned int size,
           Color col)
{
    Coordinate x = (segment.get_origin().get_abscissa() +
                    segment.get_destination().get_abscissa()) / 2;
    Coordinate y = (segment.get_origin().get_ordinate() +
                    segment.get_destination().get_ordinate()) / 2;
    aux_constructor(text, x, y, size,
                    0, 0, col);
}

Text_plt::Text_plt(const std::string& text, const Vector_plt& vector, unsigned int size,
           Color col)
{
    Coordinate x = (vector.get_origin_x() + vector.get_destination_x()) / 2;
    Coordinate y = (vector.get_origin_y() + vector.get_destination_y()) / 2;
    aux_constructor(text, x, y, size,
                    0, 0, col);
}

Text_plt::Text_plt(const Text_plt& other)
{
    content = std::string(other.content);
    abscissa = Coordinate(other.abscissa);
    ordinate = Coordinate(other.ordinate);
    size = other.size;
    offset_x = other.offset_x;
    offset_y = other.offset_y;
    color = other.color;
}

std::string Text_plt::get_content() const
{
    return content;
}

Coordinate Text_plt::get_abscissa() const
{
    return abscissa;
}

Coordinate Text_plt::get_ordinate() const
{
    return ordinate;
}

unsigned Text_plt::get_size() const
{
    return size;
}

float Text_plt::get_offset_x() const
{
    return offset_x;
}

float Text_plt::get_offset_y() const
{
    return offset_y;
}

Color Text_plt::get_color() const
{
    return color;
}

Coordinate Text_plt::get_min_abscissa() const
{
    return abscissa;
}

Coordinate Text_plt::get_max_abscissa() const
{
    return abscissa;
}

Coordinate Text_plt::get_min_ordinate() const
{
    return ordinate;
}

Coordinate Text_plt::get_max_ordinate() const
{
    return ordinate;
}
}