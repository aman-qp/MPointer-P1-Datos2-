#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <mutex>

class MPointerGC {
private:
    std::unordered_map<int, void*> pointers;  // Mapa de punteros gestionados
    std::unordered_map<int, int> refCounts;   // Mapa de contadores de referencias
    int nextId;  // Siguiente ID disponible para asignar
    std::mutex mtx;  // Mutex para proteger el acceso a los mapas

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
        std::lock_guard<std::mutex> lock(mtx);
        int id = nextId++;
        pointers[id] = ptr;
        refCounts[id] = 1;  // Inicialmente una referencia
        return id;
    }

    // Incrementa el contador de referencias para un puntero
    void IncrementRefCount(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        if (refCounts.find(id) != refCounts.end()) {
            refCounts[id]++;
        }
    }

    // Elimina un puntero del gestor y devuelve true si ya no hay más referencias
    bool RemovePointer(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        if (refCounts.find(id) != refCounts.end()) {
            refCounts[id]--;
            if (refCounts[id] == 0) {
                pointers.erase(id);
                refCounts.erase(id);
                return true;  // No hay más referencias
            }
        }
        return false;  // Aún hay referencias
    }

    // Prohíbe la copia y asignación del singleton
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif  // MPOINTERGC_H
