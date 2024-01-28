#include "Figure.h"

template <typename T>
void Areas(const Array<Figure<T>*>& A) {
    if (A._size != 0) {
        double Area;
        for (int i = 0; i < A._size; ++i) {
            Area = double(*A[i]);
            std::cout << "Area of " << A[i] -> name() << ": " << Area << std::endl;
        }
    }
}

template <typename T>
void Centers(const Array<Figure<T>*>& A) {
    if (A._size != 0) {
        Point<T> center;
        for (int i = 0; i < A._size; ++i) {
            center = A[i] -> center();
            std::cout << "Center of " << A[i] -> name() << ": " << center << std::endl;
        }
    }
}

template <typename T>
double SumArea(const Array<Figure<T>*>& A) {
    double sum {0};
    for (int i = 0; i < A._size; ++i) {
        sum += double(*A[i]);
    }

    return sum;
}