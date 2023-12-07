#pragma once

#include "Figure.h"

class ArrFigure {
    public:
        ArrFigure();
        ~ArrFigure();

        int getsize() const;
        void Centers() const;
        void Areas() const;
        void Push(Figure* obj);
        void remove(const int t);
        double SumArea() const;
        

        friend std::ostream& operator<< (std::ostream &os, const ArrFigure& f);
        
    private:
        std::size_t _size;
        Figure** Arr;
};