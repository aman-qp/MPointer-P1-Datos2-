#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>

class MPointerGC {
private:
    std::unordered_map<int, void*> pointers;  // Mapa de punteros gestionados
    int nextId;  // Siguiente ID disponible para asignar

    // Constructor privado para el patrón Singleton
    MPointerGC() : nextId(0) {}

public:
    // Metodo estático para obtener la instancia única de MPointerGC (patrón Singleton)
    static MPointerGC& GetInstance() {
        static MPointerGC instance;
        return instance;
    }

    // Agrega un puntero al gestor y devuelve un ID único
    int AddPointer(void* ptr) {
        int id = nextId++;
        pointers[id] = ptr;
        return id;
    }

    // Elimina un puntero del gestor
    void RemovePointer(int id) {
        pointers.erase(id);
    }

    // Prohíbe la copia y asignación del singleton
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif  // MPOINTERGC_H
