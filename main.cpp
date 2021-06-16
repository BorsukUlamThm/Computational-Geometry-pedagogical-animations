#include <iostream>
#include <fstream>
#include "Drawer/Model/Point.h"
#include "Drawer/Model/Segment.h"
#include "Drawer/Model/Polygon.h"

int main() {
    Point a (0, 0);
    Point b (1, 1);
    Point c (2, 2);
    Segment s(a, b);
    Polygon p({a, b, c});

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << s << std::endl;
    std::cout << p << std::endl;

    std::ofstream ofs("../test");
    ofs << a << std::endl;

    std::ifstream ifs("../test");
    std::string dummy;
    ifs >> dummy;
    Point a_;
    ifs >> a_;
    std::cout << a_ << std::endl;
}
