#include "memTracker.h"

#ifdef MEMTRACKER

static constexpr std::string_view FILENAME {"memTracker.txt"};

static constexpr float MEGABYTE {1048576.f};

perf::MemTracker perf::memTracker{};

static float asMegabytes(const long long& bytes) {
	return float(bytes) / MEGABYTE;
}

perf::MemTracker::MemTracker() : maxSnapshotTimer{600}, snapshotCounter{maxSnapshotTimer}
{
    //wyczyszczenie pliku
    std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::trunc);
		stream.close();
}

perf::MemTracker::~MemTracker()
{
    std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::app);
    if (stream.good()) 
    {
        stream << "!----------------podsumowanie-----------------!" << '\n';
        stream << "Maksymalna pamiec: " + std::to_string(asMegabytes(maxAllocatedMemory)) << " MB" << '\n';
        stream << "Cala zaalokowana pamiec: " + std::to_string(asMegabytes(allocatedMemory)) << " MB" << '\n';
        stream << "Cala zwolniona pamiec: " + std::to_string(asMegabytes(freedMemory)) << " MB" << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }
    stream.close();
}

void perf::MemTracker::snapshot()
{
    if (snapshotCounter == maxSnapshotTimer)
    {
        std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::app);
        if (stream.good())
        {
            stream << "!----------------" + std::to_string(currentSnapshot) + "-----------------!" << '\n';
            stream << "Maksymalna pamiec: " + std::to_string(asMegabytes(maxAllocatedMemory)) << " MB" << '\n';
            stream << "Cala zaalokowana pamiec: " + std::to_string(asMegabytes(allocatedMemory)) << " MB" << '\n';
            stream << "Cala zwolniona pamiec: " + std::to_string(asMegabytes(freedMemory)) << " MB" << '\n';
        }
        else
        {
            std::cerr << "Couldn't open log.txt\n";
        }
        stream.close();

        snapshotCounter = 0;
        currentSnapshot++;
    }

    snapshotCounter++;
}

void* operator new(size_t size)
{
	perf::memTracker.addAlloc(size);

	return malloc(size);
}

void* operator new[](std::size_t size)
{
    perf::memTracker.addAlloc(size);

	return malloc(size);
}

void operator delete(void* data, size_t size) noexcept
{
	perf::memTracker.addFree(size);
 
	free(data);
}

void operator delete[](void* data, std::size_t size) noexcept
{
    perf::memTracker.addFree(size);

    free (data);
}

void perf::MemTracker::addAlloc(std::size_t size)
{
    allocatedMemory += size;
    if (allocatedMemory - freedMemory > maxAllocatedMemory)
        maxAllocatedMemory = allocatedMemory - freedMemory;
    /*addMessage("New allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));*/
}

void perf::MemTracker::addFree(std::size_t size)
{
    freedMemory += size;
    /*addMessage("Freed allocation: " + std::to_string(size));
    addMessage("Currently allocated: " + std::to_string(allocatedMemory - freedMemory));
    addMessage("Currently freed: " + std::to_string(freedMemory));*/
}

void perf::MemTracker::addMessage(const std::string &message)
{
    std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::app);

    if (stream.good()) 
    {
        stream << message << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }

    stream.close();
}

#endif
