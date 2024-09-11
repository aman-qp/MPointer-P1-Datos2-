#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <list>
#include <mutex>
#include <thread>
#include <chrono>
#include <atomic>

class MPointerGC {
private:
    struct MPointerInfo {
        void* address;
        int id;
        int refCount;
    };

    std::list<MPointerInfo> pointers;
    std::mutex mtx;
    std::thread gcThread;
    std::atomic<bool> running;
    int nextId;

    MPointerGC() : nextId(0), running(false) {}

    void gcLoop() {
        while (running) {
            cleanupPointers();
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Ejecutar cada 5 segundos
        }
    }

    void cleanupPointers() {
        std::lock_guard<std::mutex> lock(mtx);
        pointers.remove_if([](const MPointerInfo& info) {
            if (info.refCount <= 0) {
                // Asumimos que info.address es un puntero a T*
                delete static_cast<char*>(info.address);  // Usamos char* como un tipo genérico
                return true;
            }
            return false;
        });
    }

public:
    static MPointerGC& GetInstance() {
        static MPointerGC instance;
        return instance;
    }

    void Initialize() {
        if (!running.exchange(true)) {
            gcThread = std::thread(&MPointerGC::gcLoop, this);
        }
    }

    void Shutdown() {
        running = false;
        if (gcThread.joinable()) {
            gcThread.join();
        }
    }

    int AddPointer(void* ptr) {
        std::lock_guard<std::mutex> lock(mtx);
        int id = nextId++;
        pointers.push_back({ptr, id, 1});
        return id;
    }

    void IncrementRefCount(int id) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& info : pointers) {
            if (info.id == id) {
                info.refCount++;
                break;
            }
        }
    }

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

    ~MPointerGC() {
        Shutdown();
    }

    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;
};

#endif // MPOINTERGC_H