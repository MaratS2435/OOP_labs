#pragma once

#include "Figure.h"
#include <iostream>

template <Coord T>
class Trapezoid : public Figure<T> {
    public:
        using Figure<T>::Pts;
        using Figure<T>::_size;
        using Figure<T>::tag;
        using Figure<T>::center;

        Trapezoid();
        Trapezoid(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
        ~Trapezoid() = default;

        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Trapezoid<U>& f);
        template <Coord U>
        friend std::ostream& operator<<(std::ostream& os, const Trapezoid<U>& f);

        std::string name() const override;

        bool isThisFigure() override;
        operator double() const override;

};

template <Coord T>
Trapezoid<T>::Trapezoid(): Figure<T>(4, 't') {}

template <Coord T>
bool Trapezoid<T>::isThisFigure() {
    Point<T> v1 = Vector(Pts[0], Pts[1]);
    Point<T> v2 = Vector(Pts[1], Pts[2]);
    Point<T> v3 = Vector(Pts[2], Pts[3]);
    Point<T> v4 = Vector(Pts[3], Pts[0]);
    if ((Scalar(v1, v3) * Scalar(v1, v3) == sqrModul(v1) * sqrModul(v3) && Scalar(v2, v4) * Scalar(v2, v4) != sqrModul(v2) * sqrModul(v4))
        || (Scalar(v1, v3) * Scalar(v1, v3) != sqrModul(v1) * sqrModul(v3) && Scalar(v2, v4) * Scalar(v2, v4) == sqrModul(v2) * sqrModul(v4)) &&
        sqrDistance(Pts[0], Pts[2]) == sqrDistance(Pts[1], Pts[3])) {

        return true;
    }
    
    return false;
}

template <Coord T>
Trapezoid<T>::Trapezoid(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4): Figure<T>(4,'t') {
    Pts.Push(p1);
    Pts.Push(p2);
    Pts.Push(p3);
    Pts.Push(p4);

    if (!isThisFigure()) {
        _size = 0;
        Pts.Arr = nullptr;
        throw std::invalid_argument("Wrong figure: Trapezoid");
    }
}

template <Coord T>
std::string Trapezoid<T>::name() const {
    return "Trapezoid";
}

template <Coord T>
Trapezoid<T>::operator double() const {
    Point<T> v1 = Vector(Pts[0], Pts[1]);
    Point<T> v3 = Vector(Pts[2], Pts[3]);
    T t1 = sqrt(sqrDistance(Pts[0], Pts[1]));
    T t2 = sqrt(sqrDistance(Pts[1], Pts[2]));
    T t3 = sqrt(sqrDistance(Pts[2], Pts[3]));
    T t4 = sqrt(sqrDistance(Pts[3], Pts[0]));
    T s;

    if (Scalar(v1, v3) * Scalar(v1, v3) == sqrModul(v1) * sqrModul(v3)) {
        s = ((t1 + t3) / 4) * sqrt(4 * t2 * t2 - (t1 - t3) * (t1 - t3));
    } else {
        s = ((t2 + t4) / 4) * sqrt(4 * t1 * t1 - (t2 - t4) * (t2 - t4));
    }

    return s;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Trapezoid<T>& f) {
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
std::ostream& operator<< (std::ostream& os, const Trapezoid<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        os << f.Pts[i] << "\n";
    }
    return os;
}
