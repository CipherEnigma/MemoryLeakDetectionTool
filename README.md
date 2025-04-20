# MemoryLeakDetectionTool
A C++ library for memory leak detection.
Memory leaks are a common and critical issue in C++ applications, often leading to inefficient resource usage and application instability. This project presents a custom Memory Leak Detection Tool implemented as a C++ library that tracks dynamic memory allocations and deallocations. By recording allocation details such as size, source file, line number, and timestamp, the tool identifies unfreed memory at runtime and reports potential leaks. Unlike heavier tools like Valgrind, this solution is lightweight, portable, and easy to integrate into any C++ codebase, making it ideal for debugging during development and improving memory management practices.

To use this run the following commands 
g++ -o build/memory_leak_tool src/memory_tracker.cpp test/main.cpp

./build/memory_leak_tool

This saves a log file inside the test folder and then using data in that file  plots a  graph.
To Plot a Graph for checking Memory leak detection make a custom Python script using matplotlib inside your test folder wherever your code is using plot_leaks.py in the repository, this will create .png file displaying the bytes of memory leaks along with line number to better visualize them.

