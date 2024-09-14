#ifndef MPOINTER_H
#define MPOINTER_H
#include "MPointerGC.h"
#include <utility>

template<typename T>
class MPointer {
private:
    T* ptr;
    int id;

public:
    void reset();
    T* get() const;

    // Constructor por defecto
    MPointer() : ptr(nullptr), id(-1) {}

    // Constructor para nullptr
    MPointer(std::nullptr_t) : ptr(nullptr), id(-1) {}

    // Constructor de copia
    MPointer(const MPointer<T>& other) : ptr(other.ptr), id(other.id) {
        if (id != -1) {
            MPointerGC::GetInstance().IncrementRefCount(id);
        }
    }

    // Operador de movimiento
    MPointer(MPointer<T>&& other) noexcept : ptr(other.ptr), id(other.id) {
        other.ptr = nullptr;
        other.id = -1;
    }

    // Función New para crear instancias de MPointer con el template T
    template<typename... Args>
    static MPointer<T> New(Args&&... args) {
        MPointer<T> mp;
        mp.ptr = new T(std::forward<Args>(args)...);
        mp.id = MPointerGC::GetInstance().AddPointer(mp.ptr);
        return mp;
    }

    // Operador de asignación para valores de tipo T
    MPointer<T>& operator=(const T& value) {
        if (ptr != nullptr) {
            // Elimina el objeto actual
            if (MPointerGC::GetInstance().RemovePointer(id)) {
                delete ptr;
            }
        }
        ptr = new T(value);
        id = MPointerGC::GetInstance().AddPointer(ptr);
        return *this;
    }


    // Operador de asignación entre dos MPointer
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            clear();
            ptr = other.ptr;
            id = other.id;
            if (id != -1) {
                MPointerGC::GetInstance().IncrementRefCount(id);
            }
        }
        return *this;
    }


    // Operador de desreferencia
    T& operator*() {
        if (ptr == nullptr) {
            throw std::runtime_error("Dereferencing null MPointer");
        }
        return *ptr;
    }

    // Operador de acceso a miembro
    T* operator->() {
        if (ptr == nullptr) {
            throw std::runtime_error("Accessing member through null MPointer");
        }
        return ptr;
    }

    const T* operator->() const {
        if (ptr == nullptr) {
            throw std::runtime_error("Accessing member through null MPointer");
        }
        return ptr;
    }

    T& operator&() {
        if (ptr == nullptr) {
            throw std::runtime_error("Accessing value of null MPointer");
        }
        return *ptr;
    }

    // Operadores de comparación con nullptr
    bool operator==(std::nullptr_t) const {
        return ptr == nullptr;
    }

    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }

    // Operador de asignación para nullptr
    MPointer<T>& operator=(std::nullptr_t) {
        clear();
        return *this;
    }

    // Operador de movimiento
    MPointer<T>& operator=(MPointer<T>&& other) noexcept {
        if (this != &other) {
            clear();
            ptr = other.ptr;
            id = other.id;
            other.ptr = nullptr;
            other.id = -1;
        }
        return *this;
    }

    // Destructor
    ~MPointer() {
        clear();
    }

private:
    void clear() {
        if (ptr != nullptr && id != -1) {
            if (MPointerGC::GetInstance().RemovePointer(id)) {
                delete ptr;
            }
        }
        ptr = nullptr;
        id = -1;
    }
};

template<typename T>
void MPointer<T>::reset() {
    clear();
}

template<typename T>
T* MPointer<T>::get() const {
    return ptr;
}

#endif  // MPOINTER_H