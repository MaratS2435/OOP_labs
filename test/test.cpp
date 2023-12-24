#include <gtest/gtest.h>
#include <map>
#include "queue.hpp"
#include <cmath>

int fact(int n){
    if (n == 0){
        return 1;
    }
    return fact(n - 1) * n;
}

TEST(map_test, test_01){
    std::map<int, int, std::less<int>, Allocator<std::pair<const int,int>>> my_map;
    my_map[0] = 1;
    for(int i = 1; i < 10; i++){
        my_map[i] = my_map[i - 1] * i;
    }
    for(int i = 0; i < 10; i++){
        ASSERT_EQ(my_map[i], fact(i));
    }
}

TEST(cotainer_test, test_01){
    Queue<int, Allocator<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    for(int i = 1; i <= q.size(); i++){
        ASSERT_EQ(q.front(), i);
        q.pop();
    }
}

TEST(cotainer_test, test_02){
    Queue<int, Allocator<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    for(int i = 1; i <= q.size(); i++){
        ASSERT_EQ(q.back(), 3);
        q.pop();
    }
}

TEST(cotainer_test, test_03){
    Queue<int, Allocator<int>> q;
    q.push(1);
    q.push(2);
    q.push(3);
    int i = 1;
    for(auto el : q){
        ASSERT_EQ(el, i++);
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}