cmake_minimum_required(VERSION 3.22)
project(advent_of_code_2022)

find_package(fmt REQUIRED)

add_executable(AOC-01 01.cpp parser.h)
target_link_libraries(AOC-01 PRIVATE fmt::fmt)
target_compile_features(AOC-01 PRIVATE cxx_std_20)
