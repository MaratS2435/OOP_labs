#include <iostream>
#include "Pentagon.h"
#include <cmath>

Pentagon::Pentagon(): Figure(5,'p') {}

bool Pentagon::isThisFigure() {
    double e {0.0000001};
    std::cout << fabs(sqrDistance(Pts[0], Pts[1]) - sqrDistance(Pts[1], Pts[2])) << "\n";
    for (int i = 1; i < 5; ++i) {
        if (fabs(sqrDistance(Pts[0], Pts[1]) - sqrDistance(Pts[i], Pts[(i + 1) % 5])) >= e)
            return false;
    }
    return true;
}

Pentagon::Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5): Figure(5,'p') {
    Pts[0] = p1;
    Pts[1] = p2;
    Pts[2] = p3;
    Pts[3] = p4;
    Pts[4] = p5;
    if (!isThisFigure()) {
        delete[] Pts;
        _size = 0;
        Pts = nullptr;
        
        throw std::invalid_argument("Wrong figure: Pentagon");
    }
}

std::string Pentagon::name() const {
    return "Pentagon";
}

Pentagon::operator double() const {
    double t = sqrDistance(Pts[0], Pts[1]);
    double s = (sqrt(5) * sqrt(5 + 2 * sqrt(5)) * t) / 4;

    return s;
}