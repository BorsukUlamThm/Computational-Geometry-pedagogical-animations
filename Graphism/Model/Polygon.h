#ifndef ALPHA_POLYGON_H
#define ALPHA_POLYGON_H

#include "Point.h"
#include <vector>


namespace gr
{
class Polygon : public Plot
{
private:
    std::vector<Point> vertices;

public:
    Polygon() = default;
    explicit Polygon(const std::vector<Point>& vertices);

    void push_back(const Point& vertex);
    void push_back(const Coordinate& x, const Coordinate& y);

    unsigned size() const;
    Point& operator[](unsigned i);
    const Point& operator[](unsigned i) const;

    Coordinate get_min_abscissa() const override;
    Coordinate get_max_abscissa() const override;
    Coordinate get_min_ordinate() const override;
    Coordinate get_max_ordinate() const override;

    friend std::istream& operator>>(std::istream& is, Polygon& polygon);
};

Polygon::Polygon(const std::vector<Point>& vertices)
{
    this->vertices = std::vector<Point>(vertices);
}

void Polygon::push_back(const Point& vertex)
{
    vertices.emplace_back(vertex);
}

void Polygon::push_back(const Coordinate& x, const Coordinate& y)
{
    vertices.emplace_back(x, y);
}

unsigned Polygon::size() const
{
    return vertices.size();
}

Point& Polygon::operator[](unsigned int i)
{
    return vertices[i];
}

const Point& Polygon::operator[](unsigned int i) const
{
    return vertices[i];
}

Coordinate Polygon::get_min_abscissa() const
{
    Coordinate res = vertices[0].get_min_abscissa();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::min(res, vertices[i].get_min_abscissa());
    }
    return res;
}

Coordinate Polygon::get_max_abscissa() const
{
    Coordinate res = vertices[0].get_max_abscissa();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::max(res, vertices[i].get_max_abscissa());
    }
    return res;
}

Coordinate Polygon::get_min_ordinate() const
{
    Coordinate res = vertices[0].get_min_ordinate();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::min(res, vertices[i].get_min_ordinate());
    }
    return res;
}

Coordinate Polygon::get_max_ordinate() const
{
    Coordinate res = vertices[0].get_max_ordinate();
    for(unsigned i = 1; i < size(); ++i)
    {
        res = std::max(res, vertices[i].get_max_ordinate());
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Polygon& polygon)
{
    os << POLYGON_NAME << " " << polygon.size() << " ";
    for(unsigned i = 0; i < polygon.size(); ++i)
    {
        os << polygon[i] << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Polygon& polygon)
{
    polygon.vertices.clear();
    unsigned nb_vertices;
    is >> nb_vertices;

    Point tmp;
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


#endif //ALPHA_POLYGON_H
