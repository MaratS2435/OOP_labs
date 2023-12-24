#pragma once

#include "Figure.hpp"

template <Coord T>
class Rhombus;
template <Coord T>
std::ostream& operator << (std::ostream &os, const Rhombus<T>& rhombus);
template <Coord T>
std::istream& operator >> (std::istream& is, Rhombus<T>& rhombus);

template <Coord T>
class Rhombus : public Figure<T>{
    friend std::ostream& operator << <>(std::ostream &os, const Rhombus<T>& rhombus);
    friend std::istream& operator >> <>(std::istream& is, Rhombus<T>& rhombus);
    Point<T> upAngle;
    Point<T> rightAngle;
    Point<T> downAngle;
    Point<T> leftAngle;
public:
    Rhombus() = default;
    Rhombus(const Rhombus<T>&) = default;
    Rhombus(const Point<T>& newUpAngle, const Point<T>& newRightAngle, const Point<T>& newDownAngle, const Point<T>& newLeftAngle);
    ~Rhombus();
    virtual Point<T> getCenter();
    virtual operator double();
    int operator==(const Rhombus<T>& other) const;
    Rhombus& operator=(const Rhombus<T>& other);
    Rhombus& operator=(Rhombus<T>&& other);
};

template <Coord T>
Rhombus<T>::Rhombus(const Point<T>& newUpAngle, const Point<T>& newRightAngle, const Point<T>& newDownAngle, const Point<T>& newLeftAngle) :
    upAngle(newUpAngle), rightAngle(newRightAngle), leftAngle(newLeftAngle), downAngle(newDownAngle){

}

template <Coord T>
Rhombus<T>::~Rhombus(){

}

template <Coord T>
Point<T> Rhombus<T>::getCenter(){
    T x = upAngle.getX();
    T y = leftAngle.getY();
    return Point<T>{x, y};
}

template <Coord T>
Rhombus<T>::operator double(){
    double diag1 = upAngle.getY() - downAngle.getY();
    double diag2 = rightAngle.getX() - leftAngle.getX();
    return diag1 * diag2 / 2;
}

template <Coord T>
std::ostream& operator << (std::ostream &os, const Rhombus<T>& rhombus){
    os << rhombus.upAngle << ' ' << rhombus.rightAngle << ' ' << rhombus.downAngle << ' ' << rhombus.leftAngle;
    return os;
}

template <Coord T>
std::istream& operator >> (std::istream& is, Rhombus<T>& rhombus){
    is >> rhombus.downAngle >> rhombus.leftAngle >> rhombus.rightAngle >> rhombus.upAngle;
    return is;
}

template <Coord T>
int Rhombus<T>::operator==(const Rhombus<T>& other) const{
    if ((upAngle == other.upAngle) and
        (rightAngle == other.rightAngle) and
        (leftAngle == other.leftAngle) and 
        (downAngle == other.downAngle)){
            return 1;
        }
    return 0;
}

template <Coord T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus<T>& other){
    if (!(this == &other)){
        upAngle = other.upAngle;
        rightAngle = other.rightAngle;
        leftAngle = other.leftAngle;
        downAngle = other.downAngle;
    }
    return *this;
}

template <Coord T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus<T>&& other){
    if (!(this == &other)){
        upAngle = other.upAngle;
        rightAngle = other.rightAngle;
        leftAngle = other.leftAngle;
        downAngle = other.downAngle;
        other.leftAngle = Point<T>(0.0, 0.0);
        other.upAngle = Point<T>(0.0, 0.0);
        other.downAngle = Point<T>(0.0, 0.0);
        other.rightAngle = Point<T>(0.0, 0.0);
    }
    return *this;
}