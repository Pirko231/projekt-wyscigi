#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

namespace perf
{

class SpeedTracker
{
public:
    static SpeedTracker& get()
    {
        static SpeedTracker tracker{360};
        return tracker;
    }
    ~SpeedTracker();

    SpeedTracker(const SpeedTracker&) = delete;
    SpeedTracker& operator=(const SpeedTracker&) = delete;

    void update();

    bool working() const {return logTime == times;}

    sf::Clock frameClock;

    sf::Time frameTime;
    sf::Time updateTime;
    sf::Time handleEventsTime;
    sf::Time displayTime;
private:
    SpeedTracker(int _logTime);

    //co ile klatek wgrywa informacje o sekundach
    int logTime;

    int times{0};
    
    sf::Time maxTime;
};

};