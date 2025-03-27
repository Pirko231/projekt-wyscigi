#include "program.h"

#ifdef SPEEDTEST
#include "speedTest.h"
#endif

#ifdef MEMTRACKER
#include "memTracker.h"
#endif

int main()
{
    Program program;

    while (program.running())
    {
        //tutaj nie dodajemy juz niczego
        //wszystko ma sie odbywac w tych trzech funkcjach
#if SPEEDTEST
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().frameClock.restart();
        sf::Time currentTime;
#endif
        program.handleEvents();
#if SPEEDTEST
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().handleEventsTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
#endif
        program.update();
#if SPEEDTEST
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().updateTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
#endif
        program.display();
#if SPEEDTEST
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().displayTime = perf::SpeedTracker::get().frameClock.getElapsedTime() - currentTime;
        currentTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
#endif

#if SPEEDTEST
        if (perf::SpeedTracker::get().working())
            perf::SpeedTracker::get().frameTime = perf::SpeedTracker::get().frameClock.getElapsedTime();
        perf::SpeedTracker::get().update();
#endif

#if MEMTRACKER
        perf::memTracker.snapshot();
#endif
    }
}