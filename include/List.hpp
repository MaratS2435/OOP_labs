#pragma once

#include "Rhombus.hpp"
#include "Pentagon.hpp"
#include "Trapezoid.hpp"
#include <memory>

template <typename T, typename U>
concept Elem = std::same_as<T, std::shared_ptr<Figure<U>>> && Coord <U>;

template <typename T, typename U> requires Elem<T, U>
class ListFigure{
    std::shared_ptr<T[]> data;
    int size;
public:
    ListFigure();
    ~ListFigure();
    ListFigure(const std::initializer_list<T> &l);
    void push(T fig);
    virtual operator double();
    void deleteFigure(int i);
    int getsize();
    std::shared_ptr<T[]> getdata();
};

template <typename T, typename U> requires Elem<T, U>
int ListFigure<T, U>::getsize(){
    return size;
}

template <typename T, typename U> requires Elem<T, U>
std::shared_ptr<T[]> ListFigure<T, U>::getdata(){
    return data;
}

template <typename T, typename U> requires Elem<T, U>
ListFigure<T, U>::ListFigure() : size{0}, data{nullptr}{

}

template <typename T, typename U> requires Elem<T, U>
ListFigure<T, U>::~ListFigure(){
}

template <typename T, typename U> requires Elem<T, U>
ListFigure<T, U>::ListFigure(const std::initializer_list<T> &l){
    data = std::make_shared<T[]>(l.size());
    size_t i = 0;
    size = 0;
    for (T f : l){
        data[i++] = f;
        size++;
    }
}

template <typename T, typename U> requires Elem<T, U>
void ListFigure<T, U>::push(T fig){
    ListFigure buf;
    buf.data = std::make_shared<T[]>(size + 1);
    for (int i = 0; i < size; i++){
        buf.data[i] = data[i];
    }
    buf.data[size] = fig;
    size++;
    data = buf.data;
}

template <typename T, typename U> requires Elem<T, U>
ListFigure<T, U>::operator double(){
    double res = 0;
    for(int i = 0; i < size; i++){
        res += double(*data[i]);
    }
    return res;
}

template <typename T, typename U> requires Elem<T, U>
void ListFigure<T, U>::deleteFigure(int i){
    ListFigure buf;
    buf.data = std::make_shared<T[]>(size - 1);
    int k = 0;
    for (int j = 0; j < size; j++){
        if (i == j){
            k = 1;
            continue;
        }
        buf.data[j - k] = data[j];
    }
    size--;
    data = buf.data;
}