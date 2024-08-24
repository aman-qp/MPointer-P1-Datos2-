cmake_minimum_required(VERSION 3.28)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 17)

# Crear la biblioteca estática, solo incluir archivos de cabecera
add_library(Proyecto_1 STATIC
        MPointer.h
        MPointerGC.h)

# Agregar el ejecutable que contiene la función main
add_executable(Proyecto_1_exe prueba.cpp)

# Vincular la biblioteca al ejecutable
target_link_libraries(Proyecto_1_exe PRIVATE Proyecto_1)

# Incluir directorios necesarios
target_include_directories(Proyecto_1_exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
