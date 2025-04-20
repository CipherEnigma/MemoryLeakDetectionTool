#include "../include/memory_tracker.h"
#include <iostream>

int main() {
    int* intPtr = TRACK_NEW(int);
    *intPtr = 42;

    int* intArray = TRACK_NEW_ARRAY(int, 5);
    for (int i = 0; i < 5; ++i) {
        intArray[i] = i * 10;
    }

    TRACK_DELETE_ARRAY(intArray);

    // Allocate another object
    double* doublePtr = TRACK_NEW(double);
    *doublePtr = 3.14;

    char* charArray = TRACK_NEW_ARRAY(char, 10);
    for (int i = 0; i < 10; ++i) {
        charArray[i] = 'A' + i;
    }

    return 0;
}
