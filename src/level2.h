#pragma once

#include "level.h"

//poziom 1 - tutaj beda funkcje i kod dla poziomu 1. Dziedziczy klase 'Level'
class Level2 : public Level
{
public:
//do public jest taka sama zasada jak w klasie 'Level'

    Level2() = delete;
    Level2(sf::RenderWindow* _window, ManagingFunctionsIterator& _managingFunctionsIterator);

    void handleEvents(sf::Event& _event);
    void update();
    void display();
private:
//calkowicie dla osoby ktora pracuje nad klasa.


};