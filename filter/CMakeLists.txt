cmake_minimum_required(VERSION 3.23)
project(filter C)

set(CMAKE_C_STANDARD 99)

add_executable(filter filter.c helpers.c helpers.h bmp.h)
