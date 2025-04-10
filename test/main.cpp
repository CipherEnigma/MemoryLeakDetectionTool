#include "../include/memory_tracker.h"

int main() {
    int* arr = TRACK_NEW_ARRAY(int, 10);
    arr[0] = 42;
    
    MemoryTracker* tracker = TRACK_NEW(MemoryTracker);
    
    TRACK_DELETE(tracker);
    TRACK_DELETE_ARRAY(arr);
    
    MemoryTracker::reportLeaks();
    return 0;
}