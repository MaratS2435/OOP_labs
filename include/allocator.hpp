#pragma once

#include <array>
#include <stdexcept>

#define MAX_SIZE 100000

template<class T>
class Allocator
{
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;

    public:
        template<class U>
        struct rebind 
        {
            using other = Allocator<U>;
        };

        Allocator();
        Allocator(const Allocator<T> &other);
        Allocator(Allocator<T> &&other) noexcept;

        T* allocate(std::size_t n);
        void deallocate(T *ptr, std::size_t n);

        template<class T1, class ... ARGS>
        void construct(T1 *p, ARGS... args);
        void destroy(T* p);

    private:
        static const size_type max_blocks = MAX_SIZE;
        size_type count_free_blocks;
        std::array<T, max_blocks> used_blocks;
        std::array<T*, max_blocks> free_blocks;
};

template<class T>
Allocator<T>::Allocator() 
{
    for(std::size_t i = 0; i < MAX_SIZE; ++i) {
        free_blocks[i] = &used_blocks[i];
    }
    count_free_blocks = MAX_SIZE;
}

template<class T>
Allocator<T>::Allocator(const Allocator<T> &other) : Allocator<T>()
{
    count_free_blocks = other.count_free_blocks;
    for(std::size_t i = 0; i < MAX_SIZE; ++i) {
        free_blocks[i] = &used_blocks[i];
        used_blocks[i] = other.used_blocks;
    }
}

template<class T>
Allocator<T>::Allocator(Allocator<T> &&other) noexcept 
{
    count_free_blocks = other.count_free_blocks;
    free_blocks = std::move(other.free_blocks);
    used_blocks = std::move(other.used_blocks);
}

template<class T>
T* Allocator<T>::allocate(std::size_t n) 
{
    if (count_free_blocks - n > MAX_SIZE)
    {
        throw std::bad_alloc();
    }
    return free_blocks[--count_free_blocks];
}

template<class T>
void Allocator<T>::deallocate(T *ptr, std::size_t n) {
        free_blocks[count_free_blocks++] = ptr;
} 

template<class T>
template<class T1, class ... ARGS>
void Allocator<T>::construct(T1 *p, ARGS... args) 
{
    new (p) T1(std::forward<ARGS>(args)...);
};

template<class T>
void Allocator<T>::destroy(T* p) 
{
    p->~T();
}