#ifndef ALPHA_POINT_2_H
#define ALPHA_POINT_2_H


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

template<typename Coordinate>
Point_2<Coordinate>::Point_2(const Coordinate& x, const Coordinate& y):
        x(x), y(y)
{}

template<typename Coordinate>
std::ostream& operator<<(std::ostream& os, const Point_2<Coordinate>& point_2)
{
    os << "(" << point_2.x << ", " << point_2.y << ")";

    return os;
}
}


#endif //ALPHA_POINT_2_H
