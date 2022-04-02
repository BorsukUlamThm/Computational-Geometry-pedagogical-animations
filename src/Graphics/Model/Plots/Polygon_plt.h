#ifndef ALPHA_POLYGON_PLT_H
#define ALPHA_POLYGON_PLT_H

#include "Point_plt.h"
#include <vector>


namespace gr
{
class Polygon_plt
{
private:
    std::vector<Point_plt> vertices;
    Color lines_color = DEFAULT_PLOT_COLOR;

public:
    Polygon_plt() = default;
    explicit Polygon_plt(Color lines_col);
    explicit Polygon_plt(const std::vector<Point_plt>& vertices,
                     Color lines_col = DEFAULT_PLOT_COLOR);
    Polygon_plt(const Polygon_plt& other);

    void push_back(const Point_plt& vertex);
    void add_vertex(const Coordinate& x, const Coordinate& y);

    unsigned size() const;
    Point_plt& operator[](unsigned i);
    const Point_plt& operator[](unsigned i) const;
    Color get_lines_color() const;

    Coordinate get_min_abscissa() const;
    Coordinate get_max_abscissa() const;
    Coordinate get_min_ordinate() const;
    Coordinate get_max_ordinate() const;

    friend std::istream& operator>>(std::istream& is, Polygon_plt& polygon);
};

Polygon_plt::Polygon_plt(Color lines_col)
{
    lines_color = lines_col;
}

Polygon_plt::Polygon_plt(const std::vector<Point_plt>& vertices, Color lines_col)
{
    this->vertices = std::vector<Point_plt>(vertices);
    lines_color = lines_col;
}

Polygon_plt::Polygon_plt(const Polygon_plt& other)
{
    for(unsigned i = 0; i < other.size(); ++i)
    {
        vertices.emplace_back(other[i]);
    }
    lines_color = other.lines_color;
}

void Polygon_plt::push_back(const Point_plt& vertex)
{
    vertices.emplace_back(vertex);
}

void Polygon_plt::add_vertex(const Coordinate& x, const Coordinate& y)
{
    vertices.emplace_back(x, y);
}

unsigned Polygon_plt::size() const
{
    return vertices.size();
}

Point_plt& Polygon_plt::operator[](unsigned int i)
{
    return vertices[i];
}

const Point_plt& Polygon_plt::operator[](unsigned int i) const
{
    return vertices[i];
}

Color Polygon_plt::get_lines_color() const
{
    return lines_color;
}

Coordinate Polygon_plt::get_min_abscissa() const
{
    Coordinate res = vertices[0].get_min_abscissa();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::min(res, vertices[i].get_min_abscissa());
    }
    return res;
}

Coordinate Polygon_plt::get_max_abscissa() const
{
    Coordinate res = vertices[0].get_max_abscissa();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::max(res, vertices[i].get_max_abscissa());
    }
    return res;
}

Coordinate Polygon_plt::get_min_ordinate() const
{
    Coordinate res = vertices[0].get_min_ordinate();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::min(res, vertices[i].get_min_ordinate());
    }
    return res;
}

Coordinate Polygon_plt::get_max_ordinate() const
{
    Coordinate res = vertices[0].get_max_ordinate();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::max(res, vertices[i].get_max_ordinate());
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Polygon_plt& polygon)
{
    os << POLYGON_NAME << " " << polygon.size() << " ";
    for(unsigned i = 0; i < polygon.size(); ++i)
    {
        os << polygon[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polygon_plt& polygon)
{
    polygon.vertices.clear();
    unsigned nb_vertices;
    is >> nb_vertices;

    Point_plt tmp;
    std::string dummy;

    for(unsigned i = 0; i < nb_vertices; ++i)
    {
        is >> dummy;
        is >> tmp;
        polygon.push_back(tmp);
    }
    return is;
}
}


#endif //ALPHA_POLYGON_PLT_H
