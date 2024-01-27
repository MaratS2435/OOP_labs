#pragma once

#include <iostream>
#include "Figure.h"

template <Coord T>
class Pentagon : public Figure<T> {
    public:
        Pentagon();
        Pentagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5);

        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Figure<U>& f);

        std::string name() const override;
        Point<T> center() const override;

    protected:
        std::shared_ptr<Point<T>[]> Pts;
        std::size_t _size = 5;
        bool isThisFigure() override;
        operator double() const;
};

#include <iostream>
#include "Pentagon.h"
#include <cmath>

template <Coord T>
Pentagon<T>::Pentagon(): Figure<T>(5,'p') {
    Pts = std::shared_ptr<Point<T>[]>(new Point<T>[4]);
}

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
    Pts = std::shared_ptr<Point<T>[]>(new Point<T>[5]);
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

template <Coord T>
Point<T> Pentagon<T>::center() const{
    Point<T> p(0, 0);
    for(int i = 0; i < _size; ++i) {
        p = p + Pts[i];
    }
    p = p / _size;
    return p;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Pentagon<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        is >> f.Pts[i].x >> f.Pts[i].y;
    }
    std::cout << f << std::endl;
    if (f.isThisFigure()) {
        return is;
    }
    throw std::invalid_argument("Incorrect figure");
}