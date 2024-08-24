#include "MPointer.h"
#include "MPointerGC.h"

// Constructor por defecto
template<typename T>
MPointer<T>::MPointer() : ptr(nullptr), id(-1) {}

// Método para crear un nuevo MPointer
template<typename T>
MPointer<T> MPointer<T>::New() {
    MPointer<T> mp;
    mp.ptr = new T;  // Asignar memoria para el tipo T
    mp.id = MPointerGC::GetInstance().AddPointer(&mp);  // Registrar el puntero en MPointerGC
    return mp;
}

// Sobrecarga del operador *
template<typename T>
T& MPointer<T>::operator*() {
    return *ptr;  // Devolver el valor referenciado
}

// Sobrecarga del operador =
template<typename T>
MPointer<T>& MPointer<T>::operator=(const MPointer<T>& other) {
    if (this != &other) {
        this->ptr = other.ptr;
        this->id = other.id;
        // Aquí podrías actualizar el contador de referencias en MPointerGC
    }
    return *this;
}

// Destructor
template<typename T>
MPointer<T>::~MPointer() {
    // Informar a MPointerGC que este puntero se está destruyendo
    MPointerGC::GetInstance().RemovePointer(this->id);
    delete ptr;
}
