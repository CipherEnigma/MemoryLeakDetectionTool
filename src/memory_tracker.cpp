#define DISABLE_NEW_MACRO
#include "../include/memory_tracker.h"
#undef DISABLE_NEW_MACRO
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <mutex>
#include <cstdlib>
#include <string>
#include <fstream> 

using namespace std;


unordered_map<void*, AllocationInfo> MemoryTracker::allocations;
mutex MemoryTracker::allocationMutex;

void* MemoryTracker::allocate(size_t size, const char* file, int line) {
    void* ptr = malloc(size);
    if (ptr) {
        lock_guard<mutex> lock(allocationMutex);
        allocations[ptr] = {size, file, line};
    }
    return ptr;
}

// Deallocate memory and remove it from tracking
void MemoryTracker::deallocate(void* ptr) {
    lock_guard<mutex> lock(allocationMutex);
    allocations.erase(ptr);
    free(ptr);
}

// Report memory leaks
void MemoryTracker::reportLeaks() {
    lock_guard<mutex> lock(allocationMutex);
    ofstream logFile("leak_report.txt"); // Open log file for writing

    if (!allocations.empty()) {
        cout << "Memory Leaks Detected:\n";
        logFile << "File,Line,Size\n"; // CSV header for Python script

        for (const auto& pair : allocations) {
            const AllocationInfo& info = pair.second;
            cout << "Leak at: " << info.file << ":" << info.line
                 << ", Size: " << info.size << " bytes\n";

            // Write leak data to log file
            logFile << info.file << "," << info.line << "," << info.size << "\n";
        }
    } else {
        cout << "No memory leaks detected.\n";
    }

    logFile.close(); 
    cout << "Generating graph using Python...\n";
    int result = system("python test/plot_leaks.py");
    if (result != 0) {
        cerr << "Error: Failed to execute Python script. Ensure Python is installed and added to PATH.\n";
    }

}

// Destructor to automatically report leaks at program exit
class MemoryLeakReporter {
public:
    ~MemoryLeakReporter() {
        MemoryTracker::reportLeaks();
    }
};

// Static instance to ensure leaks are reported at program exit
static MemoryLeakReporter memoryLeakReporter;
