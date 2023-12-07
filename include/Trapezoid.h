#pragma once

#include "Figure.h"
#include <iostream>

class Trapezoid : public Figure {
    public:
        Trapezoid();
        Trapezoid(Point p1, Point p2, Point p3, Point p4);

        std::string name() const override;

    protected:
        bool isThisFigure() override;
        operator double() const;
};