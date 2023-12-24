#pragma once
#include <iostream>
#include "point.hpp"
#include <memory>
class Figure{
    public:
        virtual ~Figure() = default;
        virtual Point<double> center() const = 0;
        explicit virtual operator double() const noexcept = 0;
        virtual void PrintCoordinates(std::ostream& os) const = 0;
        virtual std::shared_ptr<Figure> clone() const = 0;
        friend std::ostream& operator<<(std::ostream& os, const Figure& figure) {
            figure.PrintCoordinates(os);
            return os;
        }
        friend std::istream& operator>>(std::istream& is, Figure& figure) {
            figure.ReadCoordinates(is);
            return is;
        }
        virtual void ReadCoordinates(std::istream& is) = 0;
};