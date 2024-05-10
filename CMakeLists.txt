cmake_minimum_required(VERSION 3.27)
project(cdataframe C)

set(CMAKE_C_STANDARD 11)

add_executable(cdataframe
        main.c
        column.c
        column.h
        column.h)
