#pragma once
#include <iostream>
#include <stdexcept>
#include <memory>
#include "Allocator.hpp"

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node(const T& value) : data(value), next(nullptr) {}
};
template <typename T, typename Allocator = std::allocator<T>>
class CustomStack {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
public:
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(Node<T>* node) : currentNode(node) {}

        iterator& operator++() {
            if (currentNode != nullptr) {
                currentNode = currentNode->next;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const {
            return currentNode == other.currentNode;
        }

        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return currentNode->data;
        }

        pointer operator->() const {
            return currentNode->data;
        }

    private:
        Node<T>* currentNode;
    };

    using const_iterator = iterator;

    CustomStack() : head(nullptr), stackSize(0) {}

    void push(const value_type& value) {
        Node<T>* newNode = allocator.allocate(1);
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        ++stackSize;
    }
    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        Node<T>* temp = head;
        head = head->next;
        allocator.deallocate(temp, 1);
        --stackSize;
    }

    value_type& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return head->data;
    }

    const value_type& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return head->data;
    }
    bool empty() const {
        return stackSize == 0;
    }

    size_type size() const {
        return stackSize;
    }

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator cbegin() const {
        return const_iterator(head);
    }

    const_iterator cend() const {
        return const_iterator(nullptr);
    }



private:
    Node<T>* head;
    size_type stackSize;
    allocator_type allocator;
};
