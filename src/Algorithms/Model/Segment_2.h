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
    End_point origin;
    End_point destination;
};
}

#endif //ALPHA_SEGMENT_2_H
