#include <iostream>
#include <map>
#include <vector>
#include "Container_Iterator.hpp"
#include "Allocator.hpp"
int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

int main() {
    std::cout << "where" << std::endl;
    std::map<int, int, std::less<>, MyAllocator<std::pair<const int, int>, 1000>> myMapAllocator;
     for (int i = 0; i < 10; ++i) {
        myMapAllocator.emplace(i, factorial(i));
    }
    // Вывод значений на экран
    for (const auto& pair : myMapAllocator) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    MyAllocator<int, 0> allocator;
    int* ptr = allocator.allocate(3);

    for (int i = 0; i < 3; ++i) {
        ptr[i] = i;
    }

    int* new_ptr = allocator.allocate(6);

    for (int i = 0; i < 3; ++i) {
        std::cout << ptr[i] << " " << new_ptr[i] << std::endl;
    }

    allocator.deallocate(ptr, 3);
    allocator.deallocate(new_ptr, 6);

    CustomStack<int, MyAllocator<Node<int>>> myStack;

    myStack.push(5);
    myStack.push(10);
    myStack.push(15);
    for (auto it = myStack.begin(); it != myStack.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }


    return 0;
}