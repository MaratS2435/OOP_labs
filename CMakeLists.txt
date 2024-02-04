cmake_minimum_required(VERSION 3.10)
project(lab3)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} )


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

enable_testing()
add_executable(tests5 ./test/test.cpp)
target_link_libraries(tests5 ${GTEST_LIBRARIES})

add_executable(lab5 ./main.cpp)

add_test(NAME BASIC COMMAND tests5)