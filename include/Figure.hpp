#pragma once

#include "Point.hpp"

template <Coord T>
class Figure{
public:
    Figure() = default;
    Figure(const Figure<T>&) = default;
    ~Figure() = default;
    virtual Point<T> getCenter() = 0;
    virtual operator double() = 0;
};