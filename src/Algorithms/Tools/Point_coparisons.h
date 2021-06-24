#ifndef ALPHA_POINT_COPARISONS_H
#define ALPHA_POINT_COPARISONS_H

#include "../Model/Point_2.h"


namespace alg
{
template<typename Real>
bool point_below_point(const Point<Real>& p, const Point<Real>& q);
template<typename Real>
bool point_above_point(const Point<Real>& p, const Point<Real>& q);
template<typename Real>
bool point_left_point(const Point<Real>& p, const Point<Real>& q);
template<typename Real>
bool point_right_point(const Point<Real>& p, const Point<Real>& q);


template<typename Real>
Real det(const Point<Real>& p, const Point<Real>& q)
{
    return p.x * q.y - p.y * q.x;
}

template<typename Real>
Real akward_det(const Point<Real>& p, const Point<Real>& q, const Point<Real>& r)
{
    return det()
}

template<typename Real>
bool point_below_point(const Point <Real>& p, const Point <Real>& q)
{
    if (p.y == q.y)
    {
        return p.x >= q.x;
    }
    return p.y < q.y;
}

template<typename Real>
bool point_above_point(const Point <Real>& p, const Point <Real>& q)
{
    if (p.y == q.y)
    {
        return p.x <= q.x;
    }
    return p.y > q.y;
}

template<typename Real>
bool point_left_point(const Point <Real>& p, const Point <Real>& q)
{
    if (p.x == q.x)
    {
        return p.y >= q.y;
    }
    return p.x < q.x;
}

template<typename Real>
bool point_right_point(const Point <Real>& p, const Point <Real>& q)
{
    if (p.x == q.x)
    {
        return p.y <= q.y;
    }
    return p.x > q.x;
}
}

#endif //ALPHA_POINT_COPARISONS_H
