#include <gtest/gtest.h>
#include "MPointer.h"
#include "ListaDobEnlazada.h"

// Prueba para MPointer
TEST(MPointerTest, BasicOperations) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 42;
    EXPECT_EQ(*mp1, 42);

    MPointer<int> mp2 = mp1;
    EXPECT_EQ(*mp2, 42);
    EXPECT_EQ(*mp1, 42);
}

// Pruebas para ListaDobEnlazada

// Prueba para agregar elementos a la lista
TEST(ListaDobEnlazadaTest, AddElements) {
    ListaDobEnlazada lista;
    lista.append(5);
    lista.append(2);
    lista.append(9);

    EXPECT_EQ(lista.get(0), 5);
    EXPECT_EQ(lista.get(1), 2);
    EXPECT_EQ(lista.get(2), 9);
}

// Prueba para obtener elementos en posiciones específicas
TEST(ListaDobEnlazadaTest, GetElements) {
    ListaDobEnlazada lista;
    lista.append(10);
    lista.append(20);
    lista.append(30);

    EXPECT_EQ(lista.get(0), 10);
    EXPECT_EQ(lista.get(1), 20);
    EXPECT_EQ(lista.get(2), 30);
}

// Prueba para eliminar elementos de la lista
TEST(ListaDobEnlazadaTest, RemoveElements) {
    ListaDobEnlazada lista;
    lista.append(5);
    lista.append(3);
    lista.append(7);

    lista.remove(1);  // Eliminar el segundo elemento (3)

    EXPECT_EQ(lista.get(0), 5);
    EXPECT_EQ(lista.get(1), 7);
    EXPECT_EQ(lista.size(), 2);
}

// Prueba para el tamaño de la lista
TEST(ListaDobEnlazadaTest, ListSize) {
    ListaDobEnlazada lista;
    EXPECT_EQ(lista.size(), 0);

    lista.append(8);
    lista.append(12);
    EXPECT_EQ(lista.size(), 2);
}

// Prueba de iteración sobre la lista
TEST(ListaDobEnlazadaTest, IterateList) {
    ListaDobEnlazada lista;
    lista.append(1);
    lista.append(2);
    lista.append(3);

    int sum = 0;
    for (int i = 0; i < lista.size(); ++i) {
        sum += lista.get(i);
    }
    EXPECT_EQ(sum, 6);  // 1 + 2 + 3 = 6
}

// Pruebas de ordenamiento

// Prueba de BubbleSort con una lista ordenada
TEST(ListaDobEnlazadaTest, BubbleSortAlreadySorted) {
    ListaDobEnlazada lista;
    lista.append(1);
    lista.append(2);
    lista.append(3);

    lista.bubbleSort();

    EXPECT_EQ(lista.get(0), 1);
    EXPECT_EQ(lista.get(1), 2);
    EXPECT_EQ(lista.get(2), 3);
}

// Prueba de BubbleSort con una lista en orden inverso
TEST(ListaDobEnlazadaTest, BubbleSortReversed) {
    ListaDobEnlazada lista;
    lista.append(3);
    lista.append(2);
    lista.append(1);

    lista.bubbleSort();

    EXPECT_EQ(lista.get(0), 1);
    EXPECT_EQ(lista.get(1), 2);
    EXPECT_EQ(lista.get(2), 3);
}

// Prueba de QuickSort
TEST(ListaDobEnlazadaTest, QuickSort) {
    ListaDobEnlazada lista;
    lista.append(9);
    lista.append(4);
    lista.append(7);
    lista.append(1);
    lista.append(3);

    lista.quickSort();

    EXPECT_EQ(lista.get(0), 1);
    EXPECT_EQ(lista.get(1), 3);
    EXPECT_EQ(lista.get(2), 4);
    EXPECT_EQ(lista.get(3), 7);
    EXPECT_EQ(lista.get(4), 9);
}

// Prueba de InsertionSort
TEST(ListaDobEnlazadaTest, InsertionSort) {
    ListaDobEnlazada lista;
    lista.append(5);
    lista.append(1);
    lista.append(4);
    lista.append(2);
    lista.append(3);

    lista.insertionSort();

    EXPECT_EQ(lista.get(0), 1);
    EXPECT_EQ(lista.get(1), 2);
    EXPECT_EQ(lista.get(2), 3);
    EXPECT_EQ(lista.get(3), 4);
    EXPECT_EQ(lista.get(4), 5);
}

// Prueba con lista vacía en todos los algoritmos de ordenamiento
TEST(ListaDobEnlazadaTest, SortingEmptyList) {
    ListaDobEnlazada lista;

    lista.bubbleSort();
    EXPECT_EQ(lista.size(), 0);

    lista.quickSort();
    EXPECT_EQ(lista.size(), 0);

    lista.insertionSort();
    EXPECT_EQ(lista.size(), 0);
}

// Prueba con un solo elemento
TEST(ListaDobEnlazadaTest, SortingSingleElement) {
    ListaDobEnlazada lista;
    lista.append(42);

    lista.bubbleSort();
    EXPECT_EQ(lista.get(0), 42);

    lista.quickSort();
    EXPECT_EQ(lista.get(0), 42);

    lista.insertionSort();
    EXPECT_EQ(lista.get(0), 42);
}

// Prueba de ordenamiento con elementos duplicados
TEST(ListaDobEnlazadaTest, SortingWithDuplicates) {
    ListaDobEnlazada lista;
    lista.append(4);
    lista.append(1);
    lista.append(4);
    lista.append(2);
    lista.append(1);

    lista.bubbleSort();

    EXPECT_EQ(lista.get(0), 1);
    EXPECT_EQ(lista.get(1), 1);
    EXPECT_EQ(lista.get(2), 2);
    EXPECT_EQ(lista.get(3), 4);
    EXPECT_EQ(lista.get(4), 4);
}

// Pruebas adicionales de MPointer

// Verificación de asignación y liberación de memoria
TEST(MPointerTest, MemoryManagement) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 100;
    EXPECT_EQ(*mp1, 100);

    mp1.reset();  // Simula liberar el puntero
    EXPECT_EQ(mp1.get(), nullptr);
}

// Verificación de referencias múltiples
TEST(MPointerTest, MultipleReferences) {
    MPointer<int> mp1 = MPointer<int>::New();
    *mp1 = 200;

    MPointer<int> mp2 = mp1;  // Copia la referencia
    EXPECT_EQ(*mp2, 200);

    *mp2 = 300;  // Cambia el valor a través de mp2
    EXPECT_EQ(*mp1, 300);  // El valor en mp1 también debe cambiar
}

// Prueba de integración con ListaDobEnlazada usando MPointer
TEST(ListaDobEnlazadaTest, MPointerIntegration) {
    MPointer<ListaDobEnlazada> lista = MPointer<ListaDobEnlazada>::New();
    lista->append(10);
    lista->append(20);

    EXPECT_EQ(lista->get(0), 10);
    EXPECT_EQ(lista->get(1), 20);

    lista->bubbleSort();
    EXPECT_EQ(lista->get(0), 10);
    EXPECT_EQ(lista->get(1), 20);
}
