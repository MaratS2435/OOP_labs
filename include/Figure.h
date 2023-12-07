#pragma once

#include <iostream>
#include <string>
#include "Point.h"

class Figure {
    protected:
        Point* Pts;
        std::size_t _size;
        virtual bool isThisFigure();
        char tag;

    public:
        Figure();
        Figure(int n, char t);
        ~Figure() noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Figure& f);
        friend std::istream& operator>>(std::istream& is, Figure& f);

        Point center() const;
        virtual std::string name() const;


        Figure& operator= (const Figure& other);
        Figure& operator= (Figure&& other);
        bool operator== (const Figure& other) const;
        virtual operator double() const;


};