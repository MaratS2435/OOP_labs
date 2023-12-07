#pragma once

#include <iostream>
#include "Figure.h"

class Pentagon : public Figure {
    public:
        Pentagon();
        Pentagon(Point p1, Point p2, Point p3, Point p4, Point p5);

        std::string name() const override;

    protected:
        bool isThisFigure() override;
        operator double() const;
};