#pragma once

#include "Figure.h"
#include <iostream>

template <Coord T>
class Rhomb : public Figure<T> {
    public:
        Rhomb();
        Rhomb(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);

        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Figure<U>& f);

        std::string name() const override;
        Point<T> center() const override;

        std::size_t _size = 4;
        std::shared_ptr<Point<T>[]> Pts;
        bool isThisFigure() override;
        operator double() const;
};

template <Coord T>
Rhomb<T>::Rhomb(): Figure<T>(4, 'r') {
    Pts = std::shared_ptr<Point<T>[]>(new Point<T>[4]);
};

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
    Pts = std::shared_ptr<Point<T>[]>(new Point<T>[4]);
    Pts[0] = p1;
    Pts[1] = p2;
    Pts[2] = p3;
    Pts[3] = p4;
    if(!isThisFigure()) {
        Pts = nullptr;
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
Point<T> Rhomb<T>::center() const{
    Point<T> p(0, 0);
    for(int i = 0; i < _size; ++i) {
        p = p + Pts[i];
    }
    p = p / _size;
    return p;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Rhomb<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        is >> f.Pts[i].x >> f.Pts[i].y;
    }
    std::cout << f << std::endl;
    if (f.isThisFigure()) {
        return is;
    }
    throw std::invalid_argument("Incorrect figure");
}
