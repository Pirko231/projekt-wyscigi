#pragma once

#include "car.h"

//klasa dziedziczy prywatnie sf::Sprite.
class Player : public Car
{
public:
    Player();
    void handleEvents(sf::Event& ev);
private:
    
};
