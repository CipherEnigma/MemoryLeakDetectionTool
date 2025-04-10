cmake_minimum_required(VERSION 3.10)
project(MemoryLeakDetectionTool)

add_library(memory_tracker SHARED src/memory_tracker.cpp)
target_include_directories(memory_tracker PUBLIC include)
