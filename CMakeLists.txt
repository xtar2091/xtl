cmake_minimum_required(VERSION 3.0)
project(xtl)

add_compile_options(
    -std=c++11
    -g
    -O0
)

add_subdirectory(xtl)
add_subdirectory(examples)
add_subdirectory(test)
