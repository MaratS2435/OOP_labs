#pragma once
#include "figure.hpp"
#include <memory>
#include <vector>
template <class T>
class Array {
public:
    Array(size_t size) : data_(size) {}

    void add(std::shared_ptr<T> figure, size_t index) {
        if (index < data_.size()) {
            data_[index] = figure;
        }
    }

    std::shared_ptr<T> get(size_t index) const {
        if (index < data_.size()) {
            return data_[index];
        }
        return nullptr;
    }

    double totalArea() const {
        double total = 0.0;
        for (const auto& figure: data_) {
            if (figure) {
                total += figure->operator double();
            }
        }
        return total;
    }

    size_t size(){
        return data_.size();
    }

private:
    std::vector<std::shared_ptr<T>> data_;
};