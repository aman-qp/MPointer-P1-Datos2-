#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <list>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

class MPointerGC {
private:
    // Estructura que almacena la información de cada puntero gestionado por el GC.
    struct MPointerInfo {
        void* address;  // Dirección del puntero.
        int id;         // Identificador único del puntero.
        int refCount;   // Contador de referencias al puntero.
    };

    std::list<MPointerInfo> pointers;
    std::mutex mtx;
    std::thread gcThread;
    std::atomic<bool> running;
    int nextId;

    // Constructor privado (Patrón Singleton).
    MPointerGC() : nextId(0), running(false) {}

    // Bucle principal del hilo de recolección de basura.
    void gcLoop() {
        while (running) {
            cleanupPointers();  // Limpiar los punteros con refCount <= 0.
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Pausa de 5 segundos.
        }
    }

    // Elimina punteros con refCount <= 0 de la lista y libera su memoria.
    void cleanupPointers() {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.remove_if([](const MPointerInfo& info) {
            if (info.refCount <= 0) {
                // Libera la memoria del puntero si el contador de referencias es 0 o menos.
                delete static_cast<char*>(info.address);
                return true;
            }
            return false;
        });
    }

public:
    // Devuelve la instancia única del recolector de basura (Singleton).
    static MPointerGC& GetInstance() {
        static MPointerGC instance;
        return instance;
    }

    // Inicia el hilo del recolector de basura.
    void Initialize() {
        if (!running.exchange(true)) {
            gcThread = std::thread(&MPointerGC::gcLoop, this);
        }
    }

    // Detiene el hilo del recolector de basura de manera segura.
    void Shutdown() {
        running = false;
        if (gcThread.joinable()) {
            gcThread.join();
        }
    }

    // Agrega un nuevo puntero al GC y devuelve su ID único.
    int AddPointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        int id = nextId++;
        pointers.push_back({ptr, id, 1});
        return id;
    }

    // Incrementa el contador de referencias del puntero con el ID dado.
    void IncrementRefCount(int id) {
        std::lock_guard<std::mutex> lock(mtx);  // Protege el acceso a la lista.
        for (auto& info : pointers) {
            if (info.id == id) {
                info.refCount++;
                break;
            }
        }
    }

    // Disminuye el contador de referencias del puntero con el ID dado y verifica si debe ser eliminado.
    bool RemovePointer(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& info : pointers) {
            if (info.id == id) {
                info.refCount--;
                return info.refCount <= 0;
            }
        }
        return false;
    }

    // Destructor que asegura la finalización del hilo del recolector de basura.
    ~MPointerGC() {
        Shutdown();
    }

    // Elimina los métodos de copia para prevenir que se duplique la instancia del GC.
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif // MPOINTERGC_H
