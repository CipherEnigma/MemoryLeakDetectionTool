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

// Define proper macros for memory tracking
#define TRACK_NEW(TYPE) ((TYPE*)MemoryTracker::allocate(sizeof(TYPE), __FILE__, __LINE__))
#define TRACK_NEW_ARRAY(TYPE, COUNT) ((TYPE*)MemoryTracker::allocate(sizeof(TYPE) * (COUNT), __FILE__, __LINE__))
#define TRACK_DELETE(PTR) do { MemoryTracker::deallocate(PTR); (PTR) = nullptr; } while(0)
#define TRACK_DELETE_ARRAY(PTR) TRACK_DELETE(PTR) // Same implementation for simplicity


// Macro to automatically capture file and line info
#define new new(__FILE__, __LINE__)

#endif