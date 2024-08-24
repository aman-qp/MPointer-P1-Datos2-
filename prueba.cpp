#include <iostream>
#include "MPointer.h"

int main() {
    // Crear un nuevo MPointer de tipo int
    MPointer<int> mp1 = MPointer<int>::New();

    // Asignar un valor usando el operador *
    *mp1 = 42;

    // Mostrar el valor almacenado
    std::cout << "Valor almacenado en mp1: " << *mp1 << std::endl;

    // Verificar la sobrecarga del operador &
    int* rawPtr = &mp1;
    std::cout << "Dirección del puntero en mp1: " << rawPtr << std::endl;

    // Probar la asignación entre MPointers
    MPointer<int> mp2 = MPointer<int>::New();
    mp2 = mp1;

    std::cout << "Valor almacenado en mp2 (después de la asignación): " << *mp2 << std::endl;

    // Los destructores se llamarán automáticamente al salir del main
    return 0;
}
