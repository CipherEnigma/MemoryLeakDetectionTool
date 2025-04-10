#include "../include/memory_tracker.h"
#include <iostream>

int main() {
    // Allocate memory without freeing it to create a leak
    int* leakedPtr1 = new int(42);  // Leak 1
    int* leakedPtr2 = new int[10]; // Leak 2

    // Proper allocation and deallocation (no leak)
    int* ptr = new int(100);
    delete ptr;

    // Report memory leaks
    MemoryTracker::reportLeaks();  // This should report leakedPtr1 and leakedPtr2

    return 0;
}