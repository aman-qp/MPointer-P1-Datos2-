cmake_minimum_required(VERSION 3.28)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 17)

add_library(Proyecto_1 STATIC
        MPointer.cpp
        MPointer.h
        MPointerGC.h)
