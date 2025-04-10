#ifndef MEMORY_TRACKER_H
#define MEMORY_TRACKER_H

#include <iostream>
#include <cstddef>
#include <unordered_map>
#include <string>
#include <mutex>

using namespace std;

struct AllocationInfo {
    size_t size;
    string file;
    int line;
};

class MemoryTracker {
public:
    static void *allocate(size_t size, const char *file, int line);
    static void deallocate(void *ptr);
    static void reportLeaks();

private:
    static unordered_map<void *, AllocationInfo> allocations;
    static mutex allocationMutex;
};

#endif
