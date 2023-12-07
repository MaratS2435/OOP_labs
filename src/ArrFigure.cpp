#include "ArrFigure.h"
#include "Pentagon.h"
#include "Rhomb.h"
#include "Trapezoid.h"

ArrFigure::ArrFigure(): _size(0), Arr{nullptr} {}

ArrFigure::~ArrFigure() {
    _size = 0;
    delete[] Arr;
    Arr = nullptr;
}

int ArrFigure::getsize() const {
    return _size;
}

void ArrFigure::Centers() const {
    if (_size != 0) {
        Point center;
        for (int i = 0; i < _size; ++i) {
            center = Arr[i] -> center();
            std::cout << "Center of " << Arr[i] -> name() << ": " << center << std::endl;
        }
    }
}

void ArrFigure::Areas() const {
    if (_size != 0) {
        double Area;
        for (int i = 0; i < _size; ++i) {
            Area = double(*Arr[i]);
            std::cout << "Area of " << Arr[i] -> name() << ": " << Area << std::endl;
        }
    }
}

void ArrFigure::Push(Figure* obj) {
    if (_size == 0) {
        _size = 1;
        Arr = new Figure* [_size];
        Arr[0] = obj;
    } else {
        Figure** temp = Arr;
        Arr = new Figure*[_size + 1];
        if (Arr != nullptr) {
            for (int i = 0; i < _size; ++i) {
                Arr[i] = temp[i];
            }
            Arr[_size] = obj;
            _size++;
            delete[] temp;
            temp = nullptr;
        } else {
            std::cerr << "Lack of memory in ArrFigure::Push";
        }
    }
}

void ArrFigure::remove(const int t) {
    if (t >= _size || t < 0){
        throw std::invalid_argument("Non-existent element");
    }
    Figure** temp = Arr;
    Arr = new Figure*[_size - 1];
    int j {0};
    for (int i = 0; i < _size; ++i) {
        if (i != t) Arr[i - j] = temp[i];   
        else j = 1;
    }
    delete[] temp;
    temp = nullptr;
    _size--;
}

double ArrFigure::SumArea() const {
    double sum {0};
    for (int i = 0; i < _size; ++i) {
        sum += double(*Arr[i]);
    }

    return sum;
}

std::ostream& operator<< (std::ostream &os, const ArrFigure& a) {
    Point center;
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
