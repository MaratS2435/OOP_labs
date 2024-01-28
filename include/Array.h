#pragma once

#include "Figure.h"

template <typename T>
class Array {
    public:
        Array();
        ~Array() = default;

        int getsize() const;
        void Push(const T& obj);
        void remove(const int t);
        
        template <typename U>
        friend std::ostream& operator<< (std::ostream &os, const Array<U>& f);

        T operator[] (const std::size_t t) const;
        void operator= (const Array<T>& other);
        
        std::size_t _size;
        std::shared_ptr<T[]> Arr;
};

template <typename T>
Array<T>::Array(): _size(0), Arr{nullptr} {}

template <typename T>
int Array<T>::getsize() const {
    return _size;
}

template <typename T>
void Array<T>::Push(const T& obj) {
    if (_size == 0) {
        _size = 1;
        Arr = std::shared_ptr<T[]>(new T[_size]);
        Arr[0] = obj;
    } else {
        std::shared_ptr<T[]> temp = Arr;
        Arr = std::shared_ptr<T[]>(new T[_size + 1]);
        if (Arr != nullptr) {
            for (int i = 0; i < _size; ++i) {
                Arr[i] = temp[i];
            }
            Arr[_size++] = obj;
            temp = nullptr;
        } else {
            std::cerr << "Lack of memory in Array::Push";
        }
    }
}

template <typename T>
void Array<T>::remove(const int t) {
    if (t >= _size || t < 0){
        throw std::invalid_argument("Non-existent element");
    }
    std::shared_ptr<T[]> temp = Arr;
    Arr = std::shared_ptr<T[]>(new T[_size - 1]);
    int j {0};
    for (int i = 0; i < _size; ++i) {
        if (i != t) Arr[i - j] = temp[i];   
        else j = 1;
    }
    temp = nullptr;
    _size--;
}

template <typename T>
std::ostream& operator<< (std::ostream &os, const Array<T>& a) {
    for (std::size_t i = 0; i < a._size; ++i) {
        os << a.Arr[i] << "\n";
    }
    return os;
}

template <typename T>
T Array<T>::operator[] (const std::size_t t) const{
    if (t >= _size) {
        throw std::invalid_argument("Not-existent element");
    }
    return Arr[t];
}

template <typename T>
void Array<T>::operator= (const Array<T>& other) {
    _size = other._size;
    Arr = std::shared_ptr<T[]>(new T[_size]);
    for (int i = 0; i < _size; ++i) {
        Arr[i] = other.Arr[i];
    }
}

