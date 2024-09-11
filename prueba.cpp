#include <iostream>
#include "MPointer.h"
#include "ListaDobEnlazada.h"
#include <functional>

void testOperation(const std::string& opName, std::function<void()> op) {
    std::cout << "Iniciando " << opName << "..." << std::endl;
    try {
        op();
        std::cout << opName << " completado exitosamente." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error en " << opName << ": " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error desconocido en " << opName << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    MPointerGC::GetInstance().Initialize();

    std::cout << "Iniciando pruebas..." << std::endl;

    testOperation("Creación de MPointer", []() {
        MPointer<int> mp1 = MPointer<int>::New();
        *mp1 = 42;
        std::cout << "Valor almacenado en mp1: " << *mp1 << std::endl;

        MPointer<int> mp2 = MPointer<int>::New();
        mp2 = mp1;
        std::cout << "Valor almacenado en mp2 (después de la asignación): " << *mp2 << std::endl;
    });

    ListaDobEnlazada lista;

    testOperation("Adición de elementos", [&]() {
        lista.append(5);
        lista.append(2);
        lista.append(9);
        lista.append(1);
        lista.append(7);
        std::cout << "Lista original: ";
        lista.printList();
    });

    testOperation("BubbleSort", [&]() {
        std::cout << "Preparando para ejecutar BubbleSort..." << std::endl;
        try {
            lista.bubbleSort();
            std::cout << "BubbleSort completado exitosamente" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Excepción capturada durante BubbleSort: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Excepción desconocida capturada durante BubbleSort" << std::endl;
        }

        std::cout << "Lista después de BubbleSort: ";
        lista.printList();
    });

    testOperation("Adición de más elementos", [&]() {
        lista.append(8);
        lista.append(3);
        lista.append(4);
        std::cout << "Lista antes de QuickSort: ";
        lista.printList();
    });

    testOperation("QuickSort", [&]() {
        lista.quickSort();
        std::cout << "Lista después de QuickSort: ";
        lista.printList();
    });

    testOperation("Adición final de elementos", [&]() {
        lista.append(10);
        lista.append(6);
        std::cout << "Lista antes de InsertionSort: ";
        lista.printList();
    });

    testOperation("InsertionSort", [&]() {
        lista.insertionSort();
        std::cout << "Lista después de InsertionSort: ";
        lista.printList();
    });

    std::cout << "Todas las pruebas completadas." << std::endl;
    MPointerGC::GetInstance().Shutdown();
    return 0;
}