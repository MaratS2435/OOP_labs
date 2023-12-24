#include "allocator.hpp"
#include <memory>


template <class T, class Allocator = std::allocator<T>>
class Queue{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
private:    
    struct Node{
        Node * prev;
        Node * next;
        value_type value;
        bool operator!=(const Node& other) const{
            if (value != other.value) return true;
            if (prev != other.prev) return true;
            if (next != other.next) return true;
            return false;
        }
    };
public:
    class Iterator{
        Node * node;
    public:
        using difference_type = int;
        using value_type = typename Queue<T, Allocator>::value_type;
        using reference = typename Queue<T, Allocator>::reference;
        using pointer = typename Queue<T, Allocator>::pointer;
        using iterator_category = std::forward_iterator_tag;
        Iterator(Node * n){
            node = n;
        }
        Iterator& operator++() {
            node = node->prev;
            return *this;
        }

        Iterator& operator--() {
            node = node->next;
            return *this;
        }

        reference operator*() {
            return node->value;
        }

        pointer operator->() {
            return &node->value;
        }

        bool operator!=(const Iterator& other) const {
            if (node != other.node) return true;
            return false;
        }

        bool operator==(const Iterator& other) const {
            if (this != other) return false;
            return true;
        }
    };
    class ConstIterator{
        Node * node;
    public:
        using difference_type = int;
        using value_type = typename Queue<T, Allocator>::value_type;
        using reference = const typename Queue<T, Allocator>::reference;
        using pointer = const typename Queue<T, Allocator>::pointer;
        using iterator_category = std::forward_iterator_tag;
        ConstIterator(Node * n){
            node = n;
        }
        ConstIterator& operator++() {
            node = node->prev;
            return *this;
        }

        ConstIterator& operator--() {
            node = node->next;
            return *this;
        }

        reference operator*() {
            return node->value;
        }

        pointer operator->() {
            return &node->value;
        }

        bool operator!=(const ConstIterator& other) const {
            if (node != other.node) return true;
            return false;
        }

        bool operator==(const ConstIterator& other) const {
            if (this != other) return false;
            return true;
        }
    };
private:
    Allocator::template rebind<Node>::other node_alloc;
    Node * _first, * _last;
    size_t _size;
public:
    Queue(){
        _first = nullptr;
        _last = nullptr;
        _size = 0;
    }
    void push(value_type n){
        if (_first == nullptr){
            _first = node_alloc.allocate(1);
            _first->value = n;
            _first->prev = nullptr;
        } else if(_first->prev == nullptr){
            _last = node_alloc.allocate(1);
            _last->value = n;
            _last->next = _first;
            _first->prev = _last;
        } else{
            _last->next->prev = node_alloc.allocate(1);
            _last->next->prev->next = _last->next;
            _last->next = _last->next->prev;
            _last->next->prev = _last;
            _last->next->value = _last->value;
            _last->value = n;
        }
        _size++;
    }
    Queue(const Queue & other){
        _first = nullptr;
        _last = nullptr;
        _size = 0;
        Node * cur_other = other._first;
        while(cur_other != nullptr){
            push(cur_other->value);
            cur_other = cur_other->prev;
        }
    }
    Queue(const std::initializer_list<T> &l){
        _first = nullptr;
        _last = nullptr;
        _size = 0;
        for(value_type el : l){
            push(el);
        }
    }
    Queue(Queue && other){
        _size = other._size;
        _first = other._first;
        _last = other._last;
        other._size = 0;
        other._first = nullptr;
        other._last = nullptr;
    }
    ~Queue(){}
    value_type front(){
        if (_first == nullptr){
            perror("Empty queue!");
            exit(-1);
        }
        return _first->value;
    } 
    value_type back(){
        if (_first != nullptr){
            if (_first->prev == nullptr){
                return _first->value;
            }
            return _last->value;
        } 
        perror("Empty queue!");
        exit(-1);
    }
    void pop(){
        if (_first != nullptr){
            if (_first->prev == nullptr){
                node_alloc.deallocate(_first, 1);
            } else{
                _first = _first->prev;
                node_alloc.deallocate(_first->next, 1);
            }
            _size--;
        }
    }
    size_t size(){
        return _size;
    }
    int empty(){
        return (size == 0);
    }
    Iterator begin(){
        return Iterator(_first);
    }
    Iterator end(){
        return Iterator(_last->prev);
    }
    ConstIterator cbegin() {
        return ConstIterator(_first);
    }
    ConstIterator cend() {
        return ConstIterator(_last->prev);
    }
};