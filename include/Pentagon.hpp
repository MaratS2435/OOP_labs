#pragma once

#include "Figure.hpp"

template <Coord T>
class Pentagon;
template <Coord T>
std::ostream& operator << (std::ostream &os, const Pentagon<T>& Pentagon);
template <Coord T>
std::istream& operator >> (std::istream& is, Pentagon<T>& Pentagon);

template <Coord T>
class Pentagon : public Figure<T>{
    friend std::ostream& operator << <>(std::ostream &os, const Pentagon<T>& pentagon);
    friend std::istream& operator >> <>(std::istream& is, Pentagon<T>& pentagon);
    Point<T> leftUpAngle;
    Point<T> rightUpAngle;
    Point<T> leftDownAngle;
    Point<T> rightDownAngle;
    Point<T> upAngle;
public:
    Pentagon() = default;
    Pentagon(const Pentagon<T>&) = default;
    Pentagon(const Point<T>& newUpAngle, const Point<T>& newRightUpAngle, const Point<T>& newRightDownAngle, const Point<T>& newLeftDownAngle,  const Point<T>& newLeftUpAngle);
    ~Pentagon();
    virtual Point<T> getCenter();
    virtual operator double();
    int operator==(const Pentagon<T>& other) const;
    Pentagon<T>& operator=(const Pentagon<T>& other);
    Pentagon<T>& operator=(Pentagon<T>&& other);
};

template <Coord T>
Pentagon<T>::Pentagon(const Point<T>& newUpAngle, const Point<T>& newRightUpAngle, const Point<T>& newRightDownAngle, const Point<T>& newLeftDownAngle,
  const Point<T>& newLeftUpAngle) : leftUpAngle(newLeftUpAngle), leftDownAngle(newLeftDownAngle), rightDownAngle(newRightDownAngle), 
    rightUpAngle(newRightUpAngle), upAngle(newUpAngle){

}

template <Coord T>
Pentagon<T>::~Pentagon(){

}

template <Coord T>
Point<T> Pentagon<T>::getCenter(){
    double a = sqrt((upAngle.getX() - leftUpAngle.getX()) * (upAngle.getX() - leftUpAngle.getX()) + (upAngle.getY() - leftUpAngle.getY()) *  (upAngle.getY() - leftUpAngle.getY()));
    double R = a / (2 * sin(M_PI / 5));
    return Point<T>{upAngle.getX(), (upAngle.getY() - R)};
}

template <Coord T>
std::ostream& operator << (std::ostream &os, const Pentagon<T>& pentagon){
    return os << pentagon.leftDownAngle << ' ' << pentagon.leftUpAngle << ' ' << pentagon.rightDownAngle << ' ' << pentagon.rightUpAngle << ' ' << pentagon.upAngle;
}

template <Coord T>
std::istream& operator >> (std::istream& is, Pentagon<T>& pentagon){
    is >> pentagon.leftDownAngle >> pentagon.leftUpAngle >> pentagon.rightDownAngle >> pentagon.rightUpAngle >> pentagon.upAngle;
    return is;
}

template <Coord T>
Pentagon<T>::operator double(){
    double a = sqrt((upAngle.getX() - leftUpAngle.getX()) * (upAngle.getX() - leftUpAngle.getX()) + (upAngle.getY() - leftUpAngle.getY()) *  (upAngle.getY() - leftUpAngle.getY()));
    double s = 5 * a * a / (tan(M_PI / 5) * 4);
    return s; 
}

template <Coord T>
int Pentagon<T>::operator==(const Pentagon<T>& other) const{
    if ((leftUpAngle == other.leftUpAngle) and
        (rightUpAngle == other.rightUpAngle) and
        (leftDownAngle == other.leftDownAngle) and 
        (rightDownAngle == other.rightDownAngle) and
        (upAngle == other.upAngle)){
            return 1;
        }
    return 0;
}

template <Coord T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other){
    if (!(this == &other)){
        leftUpAngle = other.leftUpAngle;
        rightUpAngle = other.rightUpAngle;
        leftDownAngle = other.leftDownAngle;
        rightDownAngle = other.rightDownAngle;
        upAngle = other.upAngle;
    }
    return *this;
}

template <Coord T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& other){
    if (!(this == &other)){
        leftUpAngle = other.leftUpAngle;
        leftDownAngle = other.leftDownAngle;
        rightDownAngle = other.rightDownAngle;
        rightUpAngle = other.rightUpAngle;
        upAngle = other.upAngle;
        other.leftDownAngle = Point<T>(0.0, 0.0);
        other.leftUpAngle = Point<T>(0.0, 0.0);
        other.rightDownAngle = Point<T>(0.0, 0.0);
        other.rightUpAngle = Point<T>(0.0, 0.0);
        upAngle = Point<T>(0.0, 0.0);
    }
    return *this;
}