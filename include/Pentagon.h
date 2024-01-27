#pragma once

#include <iostream>
#include "Figure.h"

template <Coord T>
class Pentagon : public Figure<T> {
    public:
        Pentagon();
        Pentagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5);

        std::string name() const override;

    protected:
        std::shared_ptr<Point<T>[]> Pts;
        std::size_t _size;
        bool isThisFigure() override;
        operator double() const;
};

#include <iostream>
#include "Pentagon.h"
#include <cmath>

template <Coord T>
Pentagon<T>::Pentagon(): Figure<T>(5,'p') {}

template <Coord T>
bool Pentagon<T>::isThisFigure() {
    double e {0.0000001};
    for (int i = 1; i < 5; ++i) {
        if (fabs(sqrDistance(Pts[0], Pts[1]) - sqrDistance(Pts[i], Pts[(i + 1) % 5])) >= e)
            return false;
    }
    return true;
}

template <Coord T>
Pentagon<T>::Pentagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5): Figure<T>(5,'p') {
    Pts[0] = p1;
    Pts[1] = p2;
    Pts[2] = p3;
    Pts[3] = p4;
    Pts[4] = p5;
    if (!isThisFigure()) {
        _size = 0;
        Pts = nullptr;
        
        throw std::invalid_argument("Wrong figure: Pentagon");
    }
}

template <Coord T>
std::string Pentagon<T>::name() const {
    return "Pentagon";
}

template <Coord T>
Pentagon<T>::operator double() const {
    double t = sqrDistance(Pts[0], Pts[1]);
    double s = (sqrt(5) * sqrt(5 + 2 * sqrt(5)) * t) / 4;

    return s;
}