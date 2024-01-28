#pragma once

#include <iostream>
#include <string>
#include "Point.h"

template <Coord T>
class Figure {
    public:
        Array<Point<T>> Pts;
        std::size_t _size;
        char tag;
        virtual bool isThisFigure();

    
        Figure();
        Figure(int n, char t);
        ~Figure() = default;

        template <Coord U>
        friend std::ostream& operator<<(std::ostream& os, const Figure<U>& f);
        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Figure<U>& f);

        virtual Point<T> center() const;
        virtual std::string name() const;

        Figure& operator= (const Figure<T>& other);
        Figure& operator= (Figure<T>&& other);
        bool operator== (const Figure<T>& other) const;
        virtual operator double() const;

};

template <Coord T>
Figure<T>::Figure(): _size(0), tag('f') {}

template <Coord T>
Figure<T>::Figure(int n, char t) {
    tag = t;
    _size = n;
}

template <Coord T>
bool Figure<T>::isThisFigure() {
    return true;
}

template <Coord T>
std::string Figure<T>::name() const {
    return "Figure";
}

template <Coord T>
std::ostream& operator<< (std::ostream& os, const Figure<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        os << f.Pts[i] << "\n";
    }
    return os;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Figure<T>& f) {
    
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
Figure<T>::operator double() const {
    return 0;
}

template <Coord T>
Point<T> Figure<T>::center() const{
    Point<T> p(0, 0);
    for(int i = 0; i < _size; ++i) {
        p = p + Pts[i];
    }
    p = p / _size;
    return p;
}

template <Coord T>
bool Figure<T>::operator== (const Figure &other) const {
    if (other.tag != tag || double(*this) != double(other)) return false;
    
    return true;
}

template <Coord T>
Figure<T>& Figure<T>::operator= (const Figure &other) {
    tag = other.tag;
    _size = other._size;
    Pts = other.Pts;


    return *this;
}

template <Coord T>
Figure<T>& Figure<T>::operator= (Figure<T> &&other) {
    std::cout << "Bye" << std::endl;
    if (tag != other.tag) {
        throw std::underflow_error("Different figures");
    }
    if (*this != other) {
        _size = other._size;
        Pts = other.Pts;
        other.Pts = nullptr;
    }
    
    return *this;
}

