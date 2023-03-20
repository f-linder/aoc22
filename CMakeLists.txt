cmake_minimum_required(VERSION 3.22)
project(advent_of_code_2022)

find_package(fmt REQUIRED)

add_executable(AOC-01 01.cpp parser.h)
target_link_libraries(AOC-01 PRIVATE fmt::fmt)
target_compile_features(AOC-01 PRIVATE cxx_std_20)

add_executable(AOC-02 02.cpp parser.h)
target_link_libraries(AOC-02 PRIVATE fmt::fmt)
target_compile_features(AOC-02 PRIVATE cxx_std_20)

add_executable(AOC-03 03.cpp parser.h)
target_link_libraries(AOC-03 PRIVATE fmt::fmt)
target_compile_features(AOC-03 PRIVATE cxx_std_20)

add_executable(AOC-04 04.cpp parser.h)
target_link_libraries(AOC-04 PRIVATE fmt::fmt)
target_compile_features(AOC-04 PRIVATE cxx_std_20)

add_executable(AOC-05 05.cpp parser.h)
target_link_libraries(AOC-05 PRIVATE fmt::fmt)
target_compile_features(AOC-05 PRIVATE cxx_std_20)

add_executable(AOC-06 06.cpp parser.h)
target_link_libraries(AOC-06 PRIVATE fmt::fmt)
target_compile_features(AOC-06 PRIVATE cxx_std_20)

add_executable(AOC-07 07.cpp parser.h)
target_link_libraries(AOC-07 PRIVATE fmt::fmt)
target_compile_features(AOC-07 PRIVATE cxx_std_20)

add_executable(AOC-08 08.cpp parser.h)
target_link_libraries(AOC-08 PRIVATE fmt::fmt)
target_compile_features(AOC-08 PRIVATE cxx_std_20)

add_executable(AOC-09 09.cpp parser.h)
target_link_libraries(AOC-09 PRIVATE fmt::fmt)
target_compile_features(AOC-09 PRIVATE cxx_std_20)

add_executable(AOC-10 10.cpp parser.h)
target_link_libraries(AOC-10 PRIVATE fmt::fmt)
target_compile_features(AOC-10 PRIVATE cxx_std_20)

