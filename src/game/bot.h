#pragma once

#include "car.h"

class Bot : public Car
{
public:
    Bot();

    void handleEvents(sf::Event& ev);
private:

};