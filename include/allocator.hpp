#include <iostream>
#include <array>


template <class T>
class Allocator{
public:
    static constexpr size_t max_count = 332640;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    template< class U >
    struct rebind{
        typedef Allocator<U> other;
    };
private:
    char * buffer;
    std::array<void *, max_count> chunks;
    std::array<size_t, 12> chunks_count;
    const size_t chunk_size = 22720;
    size_t chunk_start(size_t n){
        return (n - 1) * chunk_size;
    }
public:
    Allocator(){
        buffer = (char *)malloc(sizeof(value_type) * max_count);
        for(size_t i = 0; i < max_count; i++){
            chunks[i] = buffer + i * sizeof(value_type);
        }
        for(size_t i = 0; i < 12; i++){
            chunks_count[i] = chunk_size / (i + 1);
        }
    }
    ~Allocator(){
        delete buffer;
        buffer = nullptr;
    }
    pointer allocate(size_t n){
        pointer res = nullptr;
        if ((n <= 12) and (chunks_count[n - 1] > 0)){
            res = (pointer)chunks[chunk_start(n) + chunks_count[n - 1] * n - 1];
            chunks_count[n - 1]--;
        }
        return res;
    }
    void deallocate(pointer p, size_t n){
        chunks[chunk_start(n) + chunks_count[n - 1] * n] = p;
        p = nullptr;
        ++chunks_count[n - 1];
    }
    template <typename U, typename... Args>
    void construct(U *p, Args &&...args){
        new (p) U(std::forward<Args>(args)...);
    }
    void destroy(pointer p){
        p->~T();
    }
};