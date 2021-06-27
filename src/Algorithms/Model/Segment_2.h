#ifndef ALPHA_SEGMENT_2_H
#define ALPHA_SEGMENT_2_H

#include "Point_2.h"

namespace alg
{
template<typename Real>
class Segment_2
{
    typedef Point_2<Real> End_point;
public:
    End_point ogn{};
    End_point dst{};

    Segment_2() = default;
    Segment_2(const End_point& ogn, const End_point& dst);
    Segment_2(const Real& x1, const Real& y1,
              const Real& x2, const Real& y2);
    ~Segment_2() = default;
};

template<typename Real>
Segment_2<Real>::Segment_2(const End_point& ogn, const End_point& dst):
    ogn(ogn), dst(dst)
{}

template<typename Real>
Segment_2<Real>::Segment_2(const Real& x1, const Real& y1,
                           const Real& x2, const Real& y2)
{
    ogn = Point_2<Real>(x1, y1);
    dst = Point_2<Real>(x2, y2);
}
}

#endif //ALPHA_SEGMENT_2_H
