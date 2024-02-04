#include <map>
#include "allocator.hpp"
#include "queue.hpp"

int main(void) {
    Queue<int, Allocator<Node<int>>> q;
    for (int i = 0; i < 10000; ++i) {
        q.push(i);
    }
    for (int i = 0; i < 10000; ++i) {
        q.pop();
    }

    std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>>> my_map;
    for (int i = 0; i < 10000; ++i) {
        my_map[i] = {i};
    }
    for (int i = 0; i < 10000; ++i) {
        my_map.erase(i);
    }
}