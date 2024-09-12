cmake_minimum_required(VERSION 3.28)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 20)

# Incluir GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Crear la biblioteca
add_library(MPointer STATIC
        MPointer.h
        MPointerGC.h
        ListaDobEnlazada.h
)
set_target_properties(MPointer PROPERTIES LINKER_LANGUAGE CXX)

# Configurar la biblioteca como header-only
target_include_directories(MPointer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Agregar el ejecutable de prueba
add_executable(Proyecto_1_exe prueba.cpp)

# Vincular la biblioteca al ejecutable de prueba
target_link_libraries(Proyecto_1_exe PRIVATE MPointer)

# Crear el ejecutable para las pruebas unitarias
add_executable(MPointer_test test.cpp)

# Vincular GTest y la biblioteca a las pruebas
target_link_libraries(MPointer_test PRIVATE MPointer GTest::GTest GTest::Main)