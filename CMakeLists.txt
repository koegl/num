cmake_minimum_required(VERSION 3.21)
project(numpy_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(num_cpp main.cpp num.cpp print.cpp print.h sorting.cpp sorting.h parsing.cpp parsing.h)


