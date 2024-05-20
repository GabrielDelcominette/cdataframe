cmake_minimum_required(VERSION 3.27)
project(DataFrame C)

set(CMAKE_C_STANDARD 11)

add_executable(DataFrame main.c
        column.c
        cdataframe.c
        almost_perfect_dataframe.h
        almost_perfect_dataframe.c
)
