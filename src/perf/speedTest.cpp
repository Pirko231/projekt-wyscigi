#include "speedTest.h"

static constexpr std::string_view FILENAME {"speedLog.txt"};

perf::SpeedTracker::SpeedTracker(int _logTime)
{
    logTime = _logTime;
    times = _logTime;
    std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::trunc);
		stream.close();
}

perf::SpeedTracker::~SpeedTracker()
{
    std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::app);
    if (stream.good())
    {
        stream << "!----------------podsumowanie-----------------!" << '\n';
        stream << "Maksymalny czas(mikrosekundy): " << maxTime.asMicroseconds() << '\n';
    }
    else 
    {
        std::cerr << "Couldn't open log.txt\n";
    }
    stream.close();
}

void perf::SpeedTracker::update()
{
    if (frameTime > maxTime)
        maxTime = frameTime;
    
    times++;
    if (times >= logTime)
    {
        std::ofstream stream(FILENAME.data(), std::ios::out | std::ios::app);

        if (stream.good())
        {
            stream << "Czas na klatke(mikrosekundy): " << frameTime.asMicroseconds() << '\n';
            stream << "Czas na funkcje update(mikrosekundy): " << updateTime.asMicroseconds() << '\n';
            stream << "Czas na funkcje handleEvents(mikrosekundy): " << handleEventsTime.asMicroseconds() << '\n';
            stream << "Czas na funkcje display(mikrosekundy): " << displayTime.asMicroseconds() << '\n';
        }
        else
        {
            std::cerr << "Couldn't open log.txt\n";
        }

        stream.close();
        times = 0;
    }
    return;
}
