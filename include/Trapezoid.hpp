#pragma once

#include "Figure.hpp"

template <Coord T>
class Trapezoid;
template <Coord T>
std::ostream& operator << (std::ostream &os, const Trapezoid<T>& Trapezoid);
template <Coord T>
std::istream& operator >> (std::istream& is, Trapezoid<T>& Trapezoid);

template <Coord T>
class Trapezoid : public Figure<T>{
    friend std::ostream& operator << <>(std::ostream &os, const Trapezoid<T>& trapezoid);
    friend std::istream& operator >> <>(std::istream& is, Trapezoid<T>& trapezoid);
    Point<T> leftUpAngle;
    Point<T> rightUpAngle;
    Point<T> leftDownAngle;
    Point<T> rightDownAngle;
public:
    Trapezoid() = default;
    Trapezoid(const Trapezoid<T>&) = default;
    Trapezoid(const Point<T>& newLeftUpAngle, const Point<T>& newRightUpAngle, const Point<T>& newLeftDownAngle, const Point<T>& newRightDownAngle);
    ~Trapezoid();
    virtual Point<T> getCenter();
    virtual operator double();
    int operator==(const Trapezoid<T>& other) const;
    Trapezoid<T>& operator=(const Trapezoid<T>& other);
    Trapezoid<T>& operator=(Trapezoid<T>&& other);
};

template <Coord T>
Trapezoid<T>::Trapezoid(const Point<T>& newLeftUpAngle, const Point<T>& newRightUpAngle, const Point<T>& newLeftDownAngle, const Point<T>& newRightDownAngle) : 
    leftUpAngle(newLeftUpAngle), leftDownAngle(newLeftDownAngle), rightDownAngle(newRightDownAngle), rightUpAngle(newRightUpAngle){

}

template <Coord T>
Trapezoid<T>::~Trapezoid(){

}

template <Coord T>
Point<T> Trapezoid<T>::getCenter(){
    T xCenter = (rightUpAngle.getX() + leftUpAngle.getX()) / 2;
    T yCenter = (rightUpAngle.getY() + rightDownAngle.getY()) / 2;
    Point<T> center{xCenter, yCenter};
    return center;
}

template <Coord T>
std::ostream& operator << (std::ostream &os, const Trapezoid<T>& trapezoid){
    return os << trapezoid.leftDownAngle << ' ' << trapezoid.leftUpAngle << ' ' << trapezoid.rightDownAngle << ' ' << trapezoid.rightUpAngle;
}

template <Coord T>
std::istream& operator >> (std::istream& is, Trapezoid<T>& trapezoid){
    is >> trapezoid.leftDownAngle >> trapezoid.leftUpAngle >> trapezoid.rightDownAngle >> trapezoid.rightUpAngle;
    return is;
}

template <Coord T>
Trapezoid<T>::operator double(){
    T h = leftUpAngle.getY() - leftDownAngle.getY();
    T a = rightUpAngle.getX() - leftUpAngle.getX();
    T b = rightDownAngle.getX() - leftDownAngle.getX();
    return h * (a + b) / 2;
}

template <Coord T>
int Trapezoid<T>::operator==(const Trapezoid<T>& other) const{
    if ((leftUpAngle == other.leftUpAngle) and
        (rightUpAngle == other.rightUpAngle) and
        (leftDownAngle == other.leftDownAngle) and 
        (rightDownAngle == other.rightDownAngle)){
            return 1;
        }
    return 0;
}

template <Coord T>
Trapezoid<T>& Trapezoid<T>::operator=(const Trapezoid<T>& other){
    if (!(this == &other)){
        leftUpAngle = other.leftUpAngle;
        rightUpAngle = other.rightUpAngle;
        leftDownAngle = other.leftDownAngle;
        rightDownAngle = other.rightDownAngle;
    }
    return *this;
}

template <Coord T>
Trapezoid<T>& Trapezoid<T>::operator=(Trapezoid<T>&& other){
    if (!(this == &other)){
        leftUpAngle = other.leftUpAngle;
        leftDownAngle = other.leftDownAngle;
        rightDownAngle = other.rightDownAngle;
        rightUpAngle = other.rightUpAngle;
        other.leftDownAngle = Point<T>(0.0, 0.0);
        other.leftUpAngle = Point<T>(0.0, 0.0);
        other.rightDownAngle = Point<T>(0.0, 0.0);
        other.rightUpAngle = Point<T>(0.0, 0.0);
    }
    return *this;
}