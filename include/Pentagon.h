#pragma once

#include <iostream>
#include "Figure.h"

template <Coord T>
class Pentagon : public Figure<T> {
    public:
        using Figure<T>::Pts;
        using Figure<T>::_size;
        using Figure<T>::tag;
        using Figure<T>::center;

        Pentagon();
        Pentagon(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4, Point<T> p5);
        ~Pentagon() = default;

        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Pentagon<U>& f);
        template <Coord U>
        friend std::ostream& operator<<(std::ostream& os, const Pentagon<U>& f);

        std::string name() const override;

        bool isThisFigure() override;
        operator double() const override;
};

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
    Pts.Push(p1);
    Pts.Push(p2);
    Pts.Push(p3);
    Pts.Push(p4);
    Pts.Push(p5);
    if (!isThisFigure()) {
        _size = 0;
        Pts.Arr = nullptr;
        
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
std::istream& operator>> (std::istream& is, Pentagon<T>& f) {
    
    for (int i = 0; i < f._size; ++i) {
        Point<T> p;
        is >> p;
        f.Pts.Push(p);
    }
    if (f.isThisFigure()) {
        return is;
    }
    throw std::invalid_argument("Incorrect figure");
}

template <Coord T>
std::ostream& operator<< (std::ostream& os, const Pentagon<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        os << '(' << f.Pts[i] << ") \n";
    }
    return os;
}