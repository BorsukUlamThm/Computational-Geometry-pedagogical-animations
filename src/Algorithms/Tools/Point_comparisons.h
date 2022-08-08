#pragma once

#include "Algorithms/Model/Point_2.h"


namespace alg
{
template<typename Real>
bool point_below_point(const Point_2<Real>& p, const Point_2<Real>& q);
template<typename Real>
bool point_above_point(const Point_2<Real>& p, const Point_2<Real>& q);
template<typename Real>
bool point_left_point(const Point_2<Real>& p, const Point_2<Real>& q);
template<typename Real>
bool point_right_point(const Point_2<Real>& p, const Point_2<Real>& q);
template<typename Real>
bool point_on_line(const Point_2<Real>& p,
                   const Point_2<Real>& ogn, const Point_2<Real>& dst);
template<typename Real>
bool point_left_line(const Point_2<Real>& p,
                     const Point_2<Real>& ogn, const Point_2<Real>& dst);
template<typename Real>
bool point_right_line(const Point_2<Real>& p,
                      const Point_2<Real>& ogn, const Point_2<Real>& dst);
template<typename Real>
bool point_strictly_left_line(const Point_2<Real>& p,
                              const Point_2<Real>& ogn, const Point_2<Real>& dst);
template<typename Real>
bool point_strictly_right_line(const Point_2<Real>& p,
                               const Point_2<Real>& ogn, const Point_2<Real>& dst);

template<typename Real>
Real det(const Point_2<Real>& p, const Point_2<Real>& q)
{
    return p.x * q.y - p.y * q.x;
}

template<typename Real>
Real akward_det(const Point_2<Real>& p, const Point_2<Real>& q, const Point_2<Real>& r)
{
    return det(q, r) - det(p, r) + det(p, q);
}

template<typename Real>
bool point_below_point(const Point_2 <Real>& p, const Point_2 <Real>& q)
{
    if (p.y == q.y)
    {
        return p.x >= q.x;
    }
    return p.y < q.y;
}

template<typename Real>
bool point_above_point(const Point_2 <Real>& p, const Point_2 <Real>& q)
{
    if (p.y == q.y)
    {
        return p.x <= q.x;
    }
    return p.y > q.y;
}

template<typename Real>
bool point_left_point(const Point_2 <Real>& p, const Point_2 <Real>& q)
{
    if (p.x == q.x)
    {
        return p.y >= q.y;
    }
    return p.x < q.x;
}

template<typename Real>
bool point_right_point(const Point_2 <Real>& p, const Point_2 <Real>& q)
{
    if (p.x == q.x)
    {
        return p.y <= q.y;
    }
    return p.x > q.x;
}
template<typename Real>
bool point_on_line(const Point_2<Real>& p,
                   const Point_2<Real>& ogn, const Point_2<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) = 0;
}

template<typename Real>
bool point_left_line(const Point_2<Real>& p,
                     const Point_2<Real>& ogn, const Point_2<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) >= 0;
}

template<typename Real>
bool point_right_line(const Point_2<Real>& p,
                      const Point_2<Real>& ogn, const Point_2<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) <= 0;
}

template<typename Real>
bool point_strictly_left_line(const Point_2<Real>& p,
                              const Point_2<Real>& ogn, const Point_2<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) > 0;
}

template<typename Real>
bool point_strictly_right_line(const Point_2<Real>& p,
                               const Point_2<Real>& ogn, const Point_2<Real>& dst)
{
    return akward_det<Real>(p, ogn, dst) < 0;
}
}