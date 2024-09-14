#include <iostream>
#include "MPointer.h"
#include "ListaDobEnlazada.h"
#include <functional>

// Función de prueba para manejar operaciones con salida
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

    testOperation("Creación y asignación de MPointer", []() {
        // Creación de MPointer
        MPointer<int> mp1 = MPointer<int>::New();
        mp1 = 42;  // Asignación directa
        std::cout << "Valor almacenado en mp1: " << *mp1 << std::endl;

        // Creación de otro MPointer y asignación
        MPointer<int> mp2 = MPointer<int>::New();
        mp2 = mp1;  // Asignación de MPointer a MPointer
        std::cout << "Valor almacenado en mp2 (después de la asignación): " << *mp2 << std::endl;

        // Demostración de la asignación directa
        mp2 = 100;  // Asignación directa a un MPointer existente
        std::cout << "Nuevo valor almacenado en mp2 (después de asignación directa): " << *mp2 << std::endl;

        // Verificar que mp1 no cambió
        std::cout << "Valor almacenado en mp1 (no debería haber cambiado): " << *mp1 << std::endl;
    });

    ListaDobEnlazada<int> lista;

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

    // Nuevas pruebas agregadas
    testOperation("Desasignación de MPointer", []() {
        MPointer<int> mp = MPointer<int>::New();
        *mp = 50;
        std::cout << "Valor inicial en mp: " << *mp << std::endl;
        mp.reset();  // Desasignación
        std::cout << "Desasignación completada. mp debería ser nullptr." << std::endl;
    });

    testOperation("Incremento y decremento de referencias de MPointer", []() {
        MPointer<int> mp1 = MPointer<int>::New();
        int id = MPointerGC::GetInstance().AddPointer(mp1.get());
        std::cout << "Valor almacenado en mp1: " << *mp1 << std::endl;

        MPointerGC::GetInstance().IncrementRefCount(id);

        MPointer<int> mp2 = MPointer<int>::New();
        MPointerGC::GetInstance().AddPointer(mp2.get());
        std::cout << "Valor almacenado en mp2: " << *mp2 << std::endl;

        MPointerGC::GetInstance().RemovePointer(id);
        std::cout << "Decremento de referencia completado. Verificar que la memoria se libera si es necesario." << std::endl;
    });

    testOperation("Eliminación de elementos en ListaDobEnlazada", [&]() {
        lista.append(10);
        lista.append(20);
        lista.append(30);
        std::cout << "Lista antes de eliminar elementos: ";
        lista.printList();
        lista.remove(1);  // Eliminar el segundo elemento
        std::cout << "Lista después de eliminar el segundo elemento: ";
        lista.printList();
    });

    testOperation("Ordenamiento de lista vacía", [&]() {
        ListaDobEnlazada<int> listaVacia;
        listaVacia.bubbleSort();
        std::cout << "Ordenamiento de lista vacía completado. Tamaño de la lista vacía: " << listaVacia.size() << std::endl;
    });

    testOperation("Ordenamiento de lista con un solo elemento", [&]() {
        ListaDobEnlazada<int> listaUnElemento;
        listaUnElemento.append(42);
        listaUnElemento.bubbleSort();
        std::cout << "Lista con un solo elemento después de BubbleSort: ";
        listaUnElemento.printList();
    });

    testOperation("Ordenamiento de lista con elementos duplicados", [&]() {
        ListaDobEnlazada<int> listaDuplicados;
        listaDuplicados.append(4);
        listaDuplicados.append(1);
        listaDuplicados.append(4);
        listaDuplicados.append(2);
        listaDuplicados.append(1);
        listaDuplicados.bubbleSort();
        std::cout << "Lista con elementos duplicados después de BubbleSort: ";
        listaDuplicados.printList();
    });

    std::cout << "Todas las pruebas completadas." << std::endl;
    MPointerGC::GetInstance().Shutdown();
    return 0;
}
