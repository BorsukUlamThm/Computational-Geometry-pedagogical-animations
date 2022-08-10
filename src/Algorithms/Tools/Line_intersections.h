#pragma once

/** @cond */
#include <iostream>
/** @endcond */
#include "Point_comparisons.h"


namespace algorithms
{
template<typename Real>
bool segment_intersect(const Segment_2<Real>& s1, const Segment_2<Real>& s2);
template<typename Real>
Point_2<Real> line_intersection(const Segment_2<Real>& s1, const Segment_2<Real>& s2);
template<typename Real>
Real x_intersection(const Segment_2<Real>& s, const Real& y);


template<typename Real>
bool segment_intersect(const Segment_2<Real>& s1, const Segment_2<Real>& s2)
{
    return akward_det(s1.ogn, s1.dst, s2.ogn) *
           akward_det(s1.ogn, s1.dst, s2.dst) <= 0;
}

template<typename Real>
Point_2<Real> line_intersection(const Segment_2<Real>& s1, const Segment_2<Real>& s2)
{
    Point_2<Real> v1 = s1.dst() - s1.ogn();
    Real a1 = v1.ord();
    Real b1 = -v1.abs();
    Real c1 = a1 * s1.ogn().abs() + b1 * s1.ogn().ord();

    Point_2<Real> v2 = s2.dst() - s2.ogn();
    Real a2 = v2.ord();
    Real b2 = -v2.abs();
    Real c2 = a2 * s2.ogn().abs() + b2 * s2.ogn().ord();

    Real x = (b2 * c1 - b1 * c2) / (a1 * b2 - a2 * b1);
    Real y = (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
    return point_2<Real>(x, y);
}

template<typename Real>
Real x_intersection(const Segment_2<Real>& s, const Real& y)
{
    if(s.ogn.y == s.dst.y)
    {
        if(s.ogn.y != y)
        {
            std::cerr << "Error : Line does not intersect x axis for y = " << y << std::endl;
            return 0;
        }
        if(s.ogn.x < s.dst.x)
        {
            return s.ogn.x;
        }
        return s.dst.x;
    }

    Real a = (s.dst.y - s.ogn.y) / (s.dst.x - s.ogn.x);
    Real b = s.ogn.y - a * s.ogn.x;
    return (y - b) / a;
}
}