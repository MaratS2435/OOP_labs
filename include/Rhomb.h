#pragma once

#include <iostream>
#include "Figure.h"

class Rhomb : public Figure {
    public:
        Rhomb();
        Rhomb(Point p1, Point p2, Point p3, Point p4);

        std::string name() const override;

    protected:
        bool isThisFigure() override;
        operator double() const;
};