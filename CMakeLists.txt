cmake_minimum_required(VERSION 3.21)
project(advent_of_code_2021 C)

set(CMAKE_C_STANDARD 99)

add_executable(sandbox common.c sandbox.c)
add_executable(Day1 common.c aoc-day-1.c)
add_executable(Day2 common.c aoc-day-2.c)
add_executable(Day3 common.c aoc-day-3.c)
