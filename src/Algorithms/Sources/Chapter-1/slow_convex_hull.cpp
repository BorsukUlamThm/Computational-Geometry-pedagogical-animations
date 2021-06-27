#include "Graphics/View/View.h"
#include "Algorithms/Model/Point_2.h"
#include "Algorithms/Model/Segment_2.h"
#include "Algorithms/Model/Polygon_2.h"
#include "Algorithms/Tools/Point_comparisons.h"


namespace chap1_slow_convex_hull
{
typedef alg::Point_2<int> point;
typedef std::vector<point> point_set;

void slow_convex_hull(const point_set& S)
{

}

int main()
{
    point_set S;
    S.push_back(point(0, 0));
    S.push_back(point(1, 0));
    S.push_back(point(0, 1));
    S.push_back(point(1, 1));

    slow_convex_hull(S);
    return 0;
}
}