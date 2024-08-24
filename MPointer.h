#ifndef MPOINTER_H
#define MPOINTER_H
#include "MPointerGC.h"

template<typename T>
class MPointer {
private:
    T* ptr;  // Puntero a la memoria que se gestionará
    int id;  // Identificador único para el puntero, asignado por MPointerGC

public:
    // Constructor por defecto
    MPointer() : ptr(nullptr), id(-1) {}

    // Metodo estático para crear un nuevo MPointer
    static MPointer<T> New() {
        MPointer<T> mp;
        mp.ptr = new T;  // Asignar memoria para el tipo T
        mp.id = MPointerGC::GetInstance().AddPointer(&mp);  // Registrar el puntero en MPointerGC
        return mp;
    }

    // Sobrecarga del operador *
    T& operator*() {
        return *ptr;  // Devolver el valor referenciado
    }

    // Sobrecarga del operador &
    T* operator&() {
        return ptr;  // Devolver la dirección del puntero
    }

    // Sobrecarga del operador =
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            // Si este MPointer ya apuntaba a otro objeto, liberar memoria y reducir la referencia
            if (this->ptr != nullptr) {
                MPointerGC::GetInstance().RemovePointer(this->id);
                delete this->ptr;
            }

            this->ptr = other.ptr;
            this->id = other.id;

            // Incrementar el contador de referencias para el nuevo puntero
            MPointerGC::GetInstance().IncrementRefCount(this->id);
        }
        return *this;
    }

    // Destructor
    ~MPointer() {
        if (this->ptr != nullptr) {
            // Informar a MPointerGC que este puntero se está destruyendo
            if (MPointerGC::GetInstance().RemovePointer(this->id)) {
                delete ptr;  // Solo eliminar si no hay más referencias
            }
        }
    }
};

#endif  // MPOINTER_H
