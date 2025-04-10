#include "../include/memory_tracker.h"
#include <iostream>
#include <cstddef>
#include <cstdlib>

using namespace std;

unordered_map<void *, AllocationInfo> MemoryTracker::allocations;
mutex MemoryTracker::allocationMutex;

void *MemoryTracker::allocate(size_t size, const char *file, int line) {
    void *ptr = malloc(size);
    if (ptr) {
        lock_guard<mutex> lock(allocationMutex);
        allocations[ptr] = {size, file, line};
    }
    return ptr;
}

void MemoryTracker::deallocate(void *ptr) {
    lock_guard<mutex> lock(allocationMutex);
    allocations.erase(ptr);
    free(ptr);
}

void MemoryTracker::reportLeaks() {
    lock_guard<mutex> lock(allocationMutex);
    if (!allocations.empty()) {
        cout << "Memory Leaks Detected:\n";
        for (const auto &pair : allocations) {
            cout << "Leak at: " << pair.second.file << ":" << pair.second.line
                 << ", Size: " << pair.second.size << " bytes\n";
        }
    }
    else{
        cout << "No memory leaks detected.\n";
    }
}