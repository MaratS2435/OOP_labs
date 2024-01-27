#pragma once

#include "Figure.h"

template <Coord T>
class ArrFigure {
    public:
        ArrFigure();
        ~ArrFigure() = default;

        int getsize() const;
        void Centers() const;
        void Areas() const;
        void Push(Figure<T>* obj);
        void remove(const int t);
        double SumArea() const;
        
        template <Coord U>
        friend std::ostream& operator<< (std::ostream &os, const ArrFigure<U>& f);
        
    private:
        std::size_t _size;
        std::shared_ptr<Figure<T>*[]> Arr;
};

#include "ArrFigure.h"
#include "Pentagon.h"
#include "Rhomb.h"
#include "Trapezoid.h"

template <Coord T>
ArrFigure<T>::ArrFigure(): _size(0), Arr{nullptr} {}

template <Coord T>
int ArrFigure<T>::getsize() const {
    return _size;
}

template <Coord T>
void ArrFigure<T>::Centers() const {
    if (_size != 0) {
        Point<T> center;
        for (int i = 0; i < _size; ++i) {
            center = Arr[i] -> center();
            std::cout << "Center of " << Arr[i] -> name() << ": " << center << std::endl;
        }
    }
}

template <Coord T>
void ArrFigure<T>::Areas() const {
    if (_size != 0) {
        double Area;
        for (int i = 0; i < _size; ++i) {
            Area = double(*Arr[i]);
            std::cout << "Area of " << Arr[i] -> name() << ": " << Area << std::endl;
        }
    }
}

template <Coord T>
void ArrFigure<T>::Push(Figure<T>* obj) {
    if (_size == 0) {
        _size = 1;
        Arr = std::shared_ptr<Figure<T>*[]>(new Figure<T>*[_size]);
        Arr[0] = obj;
    } else {
        std::shared_ptr<Figure<T>*[]> temp = Arr;
        Arr = std::shared_ptr<Figure<T>*[]>(new Figure<T>*[_size + 1]);
        if (Arr != nullptr) {
            for (int i = 0; i < _size; ++i) {
                Arr[i] = temp[i];
            }
            Arr[_size] = obj;
            _size++;
            temp = nullptr;
        } else {
            std::cerr << "Lack of memory in ArrFigure::Push";
        }
    }
}

template <Coord T>
void ArrFigure<T>::remove(const int t) {
    if (t >= _size || t < 0){
        throw std::invalid_argument("Non-existent element");
    }
    std::shared_ptr<Figure<T>*[]> temp = Arr;
    Arr = std::shared_ptr<Figure<T>*[]>(new Figure<T>*[_size - 1]);
    int j {0};
    for (int i = 0; i < _size; ++i) {
        if (i != t) Arr[i - j] = temp[i];   
        else j = 1;
    }
    temp = nullptr;
    _size--;
}

template <Coord T>
double ArrFigure<T>::SumArea() const {
    double sum {0};
    for (int i = 0; i < _size; ++i) {
        sum += double(*Arr[i]);
    }

    return sum;
}

template <Coord T>
std::ostream& operator<< (std::ostream &os, const ArrFigure<T>& a) {
    Point<T> center;
    double area;
    for (std::size_t i = 0; i < a._size; ++i) {
        os << a.Arr[i] -> name() << ' ';
        center = a.Arr[i] -> center();
        std::cout << "Center: " << center << "\t";
        area = double(*a.Arr[i]);
        std::cout <<"Area: " << area <<'\n';
    }
    return os;
}
