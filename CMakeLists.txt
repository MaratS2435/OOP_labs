cmake_minimum_required(VERSION 3.10)
project(lab4)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(lab4 main.cpp trapezoid.hpp pentagon.hpp rhombus.hpp)

enable_testing()
add_executable(tests tests.cpp trapezoid.hpp pentagon.hpp rhombus.hpp)
target_link_libraries(tests ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests)