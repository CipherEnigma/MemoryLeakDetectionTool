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
    const char* file;
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

// Macros for memory tracking
#define TRACK_NEW(TYPE) ((TYPE*)MemoryTracker::allocate(sizeof(TYPE), _FILE, __LINE_))
#define TRACK_NEW_ARRAY(TYPE, COUNT) ((TYPE*)MemoryTracker::allocate(sizeof(TYPE) * (COUNT), _FILE, __LINE_))
#define TRACK_DELETE(PTR) do { MemoryTracker::deallocate(PTR); (PTR) = nullptr; } while(0)
#define TRACK_DELETE_ARRAY(PTR) TRACK_DELETE(PTR) 


// Macro to automatically capture file and line info
#ifndef DISABLE_NEW_MACRO
#define new new(_FILE, __LINE_)
#endif

#endif