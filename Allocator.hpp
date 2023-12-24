#include <iostream>
#include <list>
#pragma once
template <typename T, size_t N = 100>
class MyAllocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, N>;
    };

    MyAllocator() : free_count(0) {}

    T* allocate(size_t) {
        free_count += N;
        return reinterpret_cast<T*>(::operator new(N * sizeof(T)));
    }
    
    void deallocate(T* p, size_t) noexcept {
        ::operator delete(p);
    }
private:
    std::list<T*> memoryBlocks;
    size_t free_count;
};
