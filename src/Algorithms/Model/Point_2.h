#ifndef ALPHA_POINT_2_H
#define ALPHA_POINT_2_H

#include "ostream"


namespace alg
{
template<typename Real>
class Point_2
{
public:
    Real x{};
    Real y{};

    Point_2() = default;
    Point_2(const Real& x, const Real& y);
    ~Point_2() = default;
};

template<typename Real>
Point_2<Real>::Point_2(const Real& x, const Real& y):
    x(x), y(y)
{}

template<typename Real>
bool operator==(const Point_2<Real>& p, const Point_2<Real>& q)
{
    return p.x == q.x && p.y == q.y;
}

template<typename Real>
std::ostream& operator<<(std::ostream& os, const Point_2<Real>& point_2)
{
    os << "(" << point_2.x << ", " << point_2.y << ")";

    return os;
}
}


#endif //ALPHA_POINT_2_H
