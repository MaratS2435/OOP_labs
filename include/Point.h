#pragma once

#include <iostream>
#include <string>
#include <cmath>
#include <concepts>
#include <memory>
#include <type_traits>
#include <vector>
#include "Array.h"

template <typename T>
concept Coord = std::is_default_constructible<T>::value || std::integral<T> || std::floating_point<T>;

template <Coord T>
class Point {
    public:
        T x;
        T y;

        Point();
        Point(T a, T b);
        Point(const Point<T>& other);
        Point(Point<T>&& other);

        template <Coord U>
        friend std::ostream& operator<< (std::ostream& os, const Point<U>& p);
        template <Coord U>
        friend std::istream& operator>> (std::istream& is, Point<U>& p);

        bool operator==(const Point<T>& other) const;
        Point& operator= (const Point<T> &other);
        Point operator* (const T &m) const;
        Point operator/ (const T &m) const;
        Point operator+ (const Point<T> &other) const;
        Point operator- (const Point<T> &other) const;
};

template <Coord T>
Point<T>::Point(): x(0), y(0){}


template <Coord T>
Point<T>::Point(T a, T b): x(a), y(b) {
}

template <Coord T>
Point<T>::Point(const Point &other) {
    x = other.x;
    y = other.y;
}

template <Coord T>
Point<T>::Point(Point<T> &&other) {
    x = other.x;
    y = other.y;
}

template <Coord T>
bool Point<T>::operator== (const Point &other) const {
    return (x == other.x && y == other.y);
}

template <Coord T>
Point<T> Point<T>::operator* (const T &m) const {
    Point res;
    res.x = x * m;
    res.y = y * m;
    return res;
}

template <Coord T>
Point<T> Point<T>::operator/ (const T &m) const {
    Point<T> res;
    res.x = x / m;
    res.y = y / m;
    return res;
}

template <Coord T>
Point<T> Point<T>::operator+ (const Point<T> &other) const{
    Point<T> res;
    res.x = x + other.x;
    res.y = y + other.y;
    return res;
}

template <Coord T>
Point<T> Point<T>::operator- (const Point<T> &other) const {
    Point<T> res;
    res.x = x - other.x;
    res.y = y - other.y;
    return res;
}

template <Coord T>
Point<T>& Point<T>::operator= (const Point<T> &other) {
    x = other.x;
    y = other.y;
    return *this;
};

template <Coord T>
std::ostream& operator<< (std::ostream& os, const Point<T>& p) {
    os << '(' << p.x << "; " << p.y << ')';
    return os;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

template <Coord T>
T sqrDistance(const Point<T> &p1, const Point<T> &p2) {
    T i, j;
    i = (p1.x - p2.x) * (p1.x - p2.x);
    j = (p1.y - p2.y) * (p1.y - p2.y);

    return i + j;
}

template <Coord T>
Point<T> Vector(const Point<T> &p1, const Point<T> &p2) {
    Point<T> res;
    res.x = p2.x - p1.x;
    res.y = p2.y - p1.y;
    
    return res;
}

template <Coord T>
T Scalar(const Point<T> &p1, const Point<T> &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

template <Coord T>
T sqrModul(const Point<T> &p) {
    return sqrDistance({0, 0}, p);
}


