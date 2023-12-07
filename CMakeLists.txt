cmake_minimum_required(VERSION 3.10)
project(lab3)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} )


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

add_executable(lab3 ./main.cpp ./src/Point.cpp ./src/Figure.cpp ./src/ArrFigure.cpp ./src/Trapezoid.cpp ./src/Rhomb.cpp ./src/Pentagon.cpp)

enable_testing()
add_executable(tests3 ./test/tests.cpp ./src/Point.cpp ./src/Figure.cpp ./src/ArrFigure.cpp ./src/Trapezoid.cpp ./src/Rhomb.cpp ./src/Pentagon.cpp)
target_link_libraries(tests3 ${GTEST_LIBRARIES})

add_test(NAME BASIC COMMAND tests3)