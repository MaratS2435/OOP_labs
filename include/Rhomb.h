#pragma once

#include "Figure.h"
#include <iostream>

template <Coord T>
class Rhomb : public Figure<T> {
    public:
        Rhomb();
        Rhomb(Point<T> p1, Point<T> p2, Point<T> p3, Point<T> p4);

        std::string name() const override;

    protected:
        std::size_t _size;
        std::shared_ptr<Point<T>[]> Pts;
        bool isThisFigure() override;
        operator double() const;
};

template <Coord T>
Rhomb<T>::Rhomb(): Figure<T>(4, 'r') {};

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
    std::cout << "h" << std::endl;
    Pts[0] = p1;
    std::cout << "e" << std::endl;
    Pts[1] = p2;
    std::cout << "l" << std::endl;
    Pts[2] = p3;
    std::cout << "l" << std::endl;
    Pts[3] = p4;
    std::cout << "o" << std::endl;
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
