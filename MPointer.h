#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"  // Incluir el gestor de memoria

template<typename T>
class MPointer {
private:
    T* ptr;  // Puntero a la memoria que se gestionará
    int id;  // Identificador único para el puntero, asignado por MPointerGC

public:
    // Constructor por defecto
    MPointer();

    // Método estático para crear un nuevo MPointer
    static MPointer<T> New();

    // Sobrecarga del operador *
    T& operator*();

    // No sobrecargaremos el operador &, ya que Clang-Tidy lo desaconseja

    // Sobrecarga del operador =
    MPointer<T>& operator=(const MPointer<T>&);

    // Destructor
    ~MPointer();
};

#endif  // MPOINTER_H
