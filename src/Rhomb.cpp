#include "Rhomb.h"
#include <iostream>

Rhomb::Rhomb(): Figure(4, 'r') {};

bool Rhomb::isThisFigure() {
    Point v1 = Vector(Pts[0], Pts[1]);
    Point v2 = Vector(Pts[1], Pts[2]);
    Point v3 = Vector(Pts[3], Pts[2]);
    Point v4 = Vector(Pts[0], Pts[3]);
    if (Scalar(v1, v3) == sqrModul(v1) && Scalar(v2,v4) == sqrModul(v2) 
        && sqrModul(v1) == sqrModul(v2)) {
        return true;
    }

    return false;
}

Rhomb::Rhomb(Point p1, Point p2, Point p3, Point p4): Figure(4, 'r') {
    Pts[0] = p1;
    Pts[1] = p2;
    Pts[2] = p3;
    Pts[3] = p4;

    if(!isThisFigure()) {
        delete[] Pts;
        Pts = nullptr;
        _size = 0;

        throw std::invalid_argument("Wrong figure: Rhomb");
    }
}

std::string Rhomb::name() const {
    return "Rhomb";
}

Rhomb::operator double() const{
    return sqrt(sqrDistance(Pts[0], Pts[2]) * sqrDistance(Pts[1], Pts[3]) / 4);
}
