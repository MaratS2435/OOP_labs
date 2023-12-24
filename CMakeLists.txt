cmake_minimum_required(VERSION 3.10)
project(lab4)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(lab5 main.cpp Container_Iterator.hpp)

enable_testing()
add_executable(tests tests.cpp Container_Iterator.hpp)
target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests)
