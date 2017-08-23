cmake_minimum_required(VERSION 3.8)
project(cdesign)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c Functions.h)
add_executable(cdesign ${SOURCE_FILES})