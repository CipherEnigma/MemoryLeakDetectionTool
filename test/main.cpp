#include "../include/memory_tracker.h"
#include <iostream>

int main() {
    // Allocate memory using TRACK_NEW
    int* intPtr = TRACK_NEW(int);
    *intPtr = 42;

    // Allocate an array using TRACK_NEW_ARRAY
    int* intArray = TRACK_NEW_ARRAY(int, 5);
    for (int i = 0; i < 5; ++i) {
        intArray[i] = i * 10;
    }

    // Intentionally forget to deallocate intPtr to simulate a memory leak

    // Properly deallocate intArray
    TRACK_DELETE_ARRAY(intArray);

    // Allocate another object
    double* doublePtr = TRACK_NEW(double);
    *doublePtr = 3.14;

    // Forget to deallocate doublePtr to simulate another memory leak

    // Program ends here, and MemoryTracker will automatically report leaks
    return 0;
}