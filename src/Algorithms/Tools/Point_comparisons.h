#ifndef ALPHA_POINT_COMPARISONS_H
#define ALPHA_POINT_COMPARISONS_H

#include "Algorithms/Model/Point_2.h"


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
bool point_on_line(const Point<Real>& p,
                   const Point<Real>& ogn, const Point<Real>& dst);
template<typename Real>
bool point_left_line(const Point<Real>& p,
                     const Point<Real>& ogn, const Point<Real>& dst);
template<typename Real>
bool point_right_line(const Point<Real>& p,
                      const Point<Real>& ogn, const Point<Real>& dst);
template<typename Real>
bool point_strictly_left_line(const Point<Real>& p,
                              const Point<Real>& ogn, const Point<Real>& dst);
template<typename Real>
bool point_strictly_right_line(const Point<Real>& p,
                               const Point<Real>& ogn, const Point<Real>& dst);

template<typename Real>
Real det(const Point<Real>& p, const Point<Real>& q)
{
    return p.x * q.y - p.y * q.x;
}

template<typename Real>
Real akward_det(const Point<Real>& p, const Point<Real>& q, const Point<Real>& r)
{
    return det(q, r) - det(p, r) + det(p, q);
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
template<typename Real>
bool point_on_line(const Point<Real>& p,
                   const Point<Real>& ogn, const Point<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) = 0;
}

template<typename Real>
bool point_left_line(const Point<Real>& p,
                     const Point<Real>& ogn, const Point<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) >= 0;
}

template<typename Real>
bool point_right_line(const Point<Real>& p,
                      const Point<Real>& ogn, const Point<Real>& dst);
{
    return akward_det<Real>(p, ogn, dst) <= 0;
}

template<typename Real>
bool point_strictly_left_line(const Point<Real>& p,
                              const Point<Real>& ogn, const Point<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) > 0;
}

template<typename Real>
bool point_strictly_right_line(const Point<Real>& p,
                               const Point<Real>& ogn, const Point<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) < 0;
}
}

#endif //ALPHA_POINT_COMPARISONS_H
