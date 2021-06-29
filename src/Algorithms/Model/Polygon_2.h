#ifndef ALPHA_POLYGON_2_H
#define ALPHA_POLYGON_2_H

#include "Point_2.h"
#include <vector>


namespace alg
{
template<typename Real>
class Polygon_2
{
    typedef Point_2<Real> Vertex;

public:
    std::vector<Vertex> vertices;

    Polygon_2() = default;
    template<typename... Points>
    explicit Polygon_2(const Vertex& p, const Points&... pts);
    ~Polygon_2() = default;

    unsigned size();

    void push_back(const Vertex& p);
    Vertex& operator[](unsigned i);
};

template<typename Real>
template<typename... Points>
Polygon_2<Real>::Polygon_2(const Vertex& p, const Points&... pts)
{
    push_back(p);
    Polygon_2(pts...);
}

template<typename Real>
unsigned Polygon_2<Real>::size()
{
    return vertices.size();
}

template<typename Real>
void Polygon_2<Real>::push_back(const Vertex& p)
{
    vertices.push_back(p);
}

template<typename Real>
typename Polygon_2<Real>::Vertex& Polygon_2<Real>::operator[](unsigned int i)
{
    return vertices[i];
}
}


#endif //ALPHA_POLYGON_2_H
