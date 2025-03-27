#pragma once

#include <iostream>
#include <fstream>

#pragma GCC diagnostic ignored "-Wsized-deallocation"

void* operator new(std::size_t size);
void* operator new[](std::size_t size);

void operator delete(void* data, std::size_t size) noexcept;
void operator delete[](void* data, std::size_t size) noexcept;

namespace perf
{

class MemTracker
{
public:
    MemTracker();
    MemTracker(const MemTracker&) = delete;
    MemTracker& operator=(const MemTracker&) = delete;
    ~MemTracker();

    void snapshot();

    void addAlloc(std::size_t size);
    void addFree(std::size_t size);
    void addMessage(const std::string&);
private:
    const int maxSnapshotTimer;

    int snapshotCounter{0};

    int currentSnapshot{0};

    long long int allocatedMemory{0};

    long long int freedMemory{0};

    long long int maxAllocatedMemory{0};
};

    extern MemTracker memTracker;
};