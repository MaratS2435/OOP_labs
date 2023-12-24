#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <concepts>

template <typename T>
concept Coord = std::is_default_constructible<T>::value || std::integral<T> || std::floating_point<T>;

template <Coord T>
class Point;
template <Coord T>
std::ostream& operator << (std::ostream &os, const Point<T>& point);
template <Coord T>
std::istream& operator >> (std::istream& is, Point<T>& point);


template<Coord T>
class Point{
    friend std::ostream& operator << <>(std::ostream &os, const Point<T>& point);
    friend std::istream& operator >> <>(std::istream& is, Point<T>& point);
    T x;
    T y;
public:
    Point() = default;
    Point(T newX, T newY);
    Point(const Point<T>& other);
    ~Point();
    T getX();
    T getY();
    int operator ==(const Point<T>& other) const;
    Point<T>& operator=(const Point<T>& other);
};

template<Coord T>
Point<T>::Point(T newX, T newY) : x(newX), y(newY){

}

template<Coord T>
Point<T>::~Point(){

}

template<Coord T>
Point<T>::Point(const Point& other){
    x = other.x;
    y = other.y;
}

template<Coord T>
T Point<T>::getX(){
    return x;
}

template<Coord T>
T Point<T>::getY(){
    return y;
}

template<Coord T>
std::ostream& operator << (std::ostream &os, const Point<T>& point){
    return os << point.x << ' ' << point.y;
}

template<Coord T>
std::istream& operator >> (std::istream& is, Point<T>& point){
    is >> point.x;
    is >> point.y;
    return is;
}

template<Coord T>
int Point<T>::operator==(const Point& other) const{
    if ((x == other.x) and (y == other.y)){
        return 1;
    }
    return 0;
}

template<Coord T>
Point<T>& Point<T>::operator=(const Point& other){
    x = other.x;
    y = other.y;
    return *this;
}