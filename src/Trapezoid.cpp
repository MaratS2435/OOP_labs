#include <iostream>
#include <math.h>
#include "Trapezoid.h"

Trapezoid::Trapezoid(): Figure(4, 't') {}

bool Trapezoid::isThisFigure() {
    Point v1 = Vector(Pts[0], Pts[1]);
    Point v2 = Vector(Pts[1], Pts[2]);
    Point v3 = Vector(Pts[2], Pts[3]);
    Point v4 = Vector(Pts[3], Pts[0]);
    if ((Scalar(v1, v3) * Scalar(v1, v3) == sqrModul(v1) * sqrModul(v3) && Scalar(v2, v4) * Scalar(v2, v4) != sqrModul(v2) * sqrModul(v4))
        || (Scalar(v1, v3) * Scalar(v1, v3) != sqrModul(v1) * sqrModul(v3) && Scalar(v2, v4) * Scalar(v2, v4) == sqrModul(v2) * sqrModul(v4)) &&
        sqrDistance(Pts[0], Pts[2]) == sqrDistance(Pts[1], Pts[3])) {

        return true;
    }
    
    return false;
}

Trapezoid::Trapezoid(Point p1, Point p2, Point p3, Point p4): Figure(4,'t') {
    Pts[0] = p1;
    Pts[1] = p2;
    Pts[2] = p3;
    Pts[3] = p4;

    if (!isThisFigure()) {
        delete[] Pts;
        _size = 0;
        Pts = nullptr;
        throw std::invalid_argument("Wrong figure: Trapezoid");
    }
}

std::string Trapezoid::name() const {
    return "Trapezoid";
}

Trapezoid::operator double() const {
    Point v1 = Vector(Pts[0], Pts[1]);
    Point v3 = Vector(Pts[2], Pts[3]);
    double t1 = sqrt(sqrDistance(Pts[0], Pts[1]));
    double t2 = sqrt(sqrDistance(Pts[1], Pts[2]));
    double t3 = sqrt(sqrDistance(Pts[2], Pts[3]));
    double t4 = sqrt(sqrDistance(Pts[3], Pts[0]));
    double s;

    if (Scalar(v1, v3) * Scalar(v1, v3) == sqrModul(v1) * sqrModul(v3)) {
        s = ((t1 + t3) / 4) * sqrt(4 * t2 * t2 - (t1 - t3) * (t1 - t3));
    } else {
        s = ((t2 + t4) / 4) * sqrt(4 * t1 * t1 - (t2 - t4) * (t2 - t4));
    }

    return s;
}


