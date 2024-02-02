#include "allocator.hpp"
#include <memory>

template <class T>
class Node{
    public:
        Node<T> * next;
        T value;
        bool operator!=(const Node<T>& other) const{
            if (value != other.value) return true;
            if (next != other.next) return true;
            return false;
        }
};

template <class T, class Allocator>
class Queue{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
private:    
    
public:
    class Iterator{
    
    public:
        using difference_type = int;
        using value_type = typename Queue<T, Allocator>::value_type;
        using reference = typename Queue<T, Allocator>::reference;
        using pointer = typename Queue<T, Allocator>::pointer;
        using iterator_category = std::forward_iterator_tag;
        Iterator(Node<value_type> * n){
            node = n;
        }
        Iterator& operator++() {
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
        private:
            Node<value_type> * node;
    };
    class ConstIterator{
    public:
        using difference_type = int;
        using value_type = typename Queue<T, Allocator>::value_type;
        using reference = const typename Queue<T, Allocator>::reference;
        using pointer = const typename Queue<T, Allocator>::pointer;
        using iterator_category = std::forward_iterator_tag;
        ConstIterator(Node<value_type> * n){
            node = n;
        }
        ConstIterator& operator++() {
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

        private:

            Node<value_type> * node;

    };
private:
    Allocator node_alloc;
    Node<value_type> * _head, * _tail;
    //size_t _size;
public:
    Queue(){
        _head = nullptr;
        _tail = nullptr;
        //_size = 0;
    }

    void empty() const{
        return (_head == nullptr);
    }

    void push(value_type n){
        if (empty()) {
            _head = node_alloc.allocate(1);
            _head -> value = n;
            _tail = _head;
        } else {
            Node<value_type>* temp = node_alloc.allocate(1);
            temp -> value = n;
            _tail -> next = temp;
            _tail = temp;
            _tail -> next = nullptr;
        }
        //_size++;
    }
    Queue(const Queue & other){
        _head = nullptr;
        _tail = nullptr;
        //_size = 0;
        Node<value_type> * cur_other = other._head;
        while(cur_other != nullptr){
            push(cur_other->value);
            cur_other = cur_other->next;
        }
    }
    Queue(const std::initializer_list<T> &l){
        _head = nullptr;
        _tail = nullptr;
        //_size = 0;
        for(value_type el : l){
            push(el);
        }
    }
    Queue(Queue && other){
        //_size = other._size;
        _head = other._head;
        _tail = other._tail;
        //other._size = 0;
        other._head = nullptr;
        other._tail = nullptr;
    }

    ~Queue(){}

    value_type front(){
        if (_head == nullptr){
            perror("Empty queue!");
            exit(-1);
        }
        return _head->value;
    } 
    value_type back(){
        if (_tail != nullptr) return _tail->value; 
        perror("Empty queue!");
        exit(-1);
    }
    void pop(){
        if (_head != nullptr){
            if (_head->next == nullptr){
                node_alloc.deallocate(_head, 1);
                _head = nullptr;
                _tail = nullptr;
            } else {
                Node<value_type>* temp = _head;
                _head = _head->next;
                node_alloc.deallocate(temp, 1);
            }
            //_size--;
        }
    }
    /*size_t size(){
        return _size;
    }*/
    int empty(){
        return (_head == nullptr);
    }
    Iterator begin(){
        return Iterator(_head);
    }
    Iterator end(){
        return Iterator(_tail->next);
    }
    ConstIterator cbegin() {
        return ConstIterator(_head);
    }
    ConstIterator cend() {
        return ConstIterator(_tail->next);
    }
};