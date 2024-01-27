#pragma once

#include <iostream>
#include <string>
#include "Point.h"

template <Coord T>
class Figure {
    protected:
        std::shared_ptr<Point<T>[]> Pts;
        std::size_t _size;
        virtual bool isThisFigure();
        char tag;

    public:
        Figure();
        Figure(int n, char t);
        ~Figure() = default;

        template <Coord U>
        friend std::ostream& operator<<(std::ostream& os, const Figure<U>& f);
        template <Coord U>
        friend std::istream& operator>>(std::istream& is, Figure<U>& f);

        Point<T> center() const;
        virtual std::string name() const;


        Figure<T>& operator= (const Figure<T>& other);
        Figure<T>& operator= (Figure<T>&& other);
        bool operator== (const Figure<T>& other) const;
        virtual operator double() const;


};

template <Coord T>
Figure<T>::Figure(): _size(0), Pts{nullptr}, tag('f') {}

template <Coord T>
Figure<T>::Figure(int n, char t) {
    tag = t;
    _size = n;
    Pts = std::shared_ptr<Point<T>[]>(new Point<T>[_size]);
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
        os << '(' << f.Pts[i].x << ';' << f.Pts[i].y << ") \n";
    }
    return os;
}

template <Coord T>
std::istream& operator>> (std::istream& is, Figure<T>& f) {
    for (int i = 0; i < f._size; ++i) {
        is >> f.Pts[i].x >> f.Pts[i].y;
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
    if (other.tag == tag) {
        _size = other._size;
        Pts = std::shared_ptr<Point<T>[]>(new Point<T> [_size]);
        for (int i = 0; i < _size; ++i) {
            Pts[i] = other.Pts[i];
        }
    } else {
        throw std::underflow_error("Different figures");
    }

    return *this;
}

template <Coord T>
Figure<T>& Figure<T>::operator= (Figure<T> &&other) {
    if (tag != other.tag) {
        throw std::underflow_error("Different figures");
    }
    if (*this != other) {
        _size = other._size;
        delete [] Pts;
        Pts = other.Pts;
        other.Pts = nullptr;
    }
    
    return *this;
}

