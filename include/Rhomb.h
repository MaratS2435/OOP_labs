#pragma once

#include "Figure.h"
#include <iostream>

template <Coord T>
class Rhomb : public Figure<T> {
    public:
        using Figure<T>::Pts;
        using Figure<T>::_size;
        using Figure<T>::tag;
        using Figure<T>::center;

        Rhomb();
        Rhomb(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);
        ~Rhomb() = default;

        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Rhomb<U>& f);
        template <Coord U>
        friend std::ostream& operator<<(std::ostream& os, const Rhomb<U>& f);

        std::string name() const override;

        bool isThisFigure() override;
        operator double() const override;

};

template <Coord T>
Rhomb<T>::Rhomb(): Figure<T>(4, 'r') {}

template <Coord T>
bool Rhomb<T>::isThisFigure() {
    Point<T> v1 = Vector(Pts[0], Pts[1]);
    Point<T> v2 = Vector(Pts[1], Pts[2]);
    Point<T> v3 = Vector(Pts[3], Pts[2]);
    Point<T> v4 = Vector(Pts[0], Pts[3]);
    if (Scalar(v1, v3) == sqrModul(v1) && Scalar(v2,v4) == sqrModul(v2) 
        && sqrModul(v1) == sqrModul(v2)) {
        return true;
    }

    return false;
}

template <Coord T>
Rhomb<T>::Rhomb(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4): Figure<T>(4, 'r') {
    Pts.Push(p1);
    Pts.Push(p2);
    Pts.Push(p3);
    Pts.Push(p4);

    if(!isThisFigure()) {
        Pts.Arr = nullptr;
        _size = 0;

        throw std::invalid_argument("Wrong figure: Rhomb");
    }
}

template <Coord T>
std::string Rhomb<T>::name() const {
    return "Rhomb";
}

template <Coord T>
Rhomb<T>::operator double() const{
   
    return sqrt(sqrDistance(Pts[0], Pts[2]) * sqrDistance(Pts[1], Pts[3]) / 4);
}

template <Coord T>
std::istream& operator>> (std::istream& is, Rhomb<T>& f) {
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
std::ostream& operator<< (std::ostream& os, const Rhomb<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        os << f.Pts[i] << "\n";
    }
    return os;
}
