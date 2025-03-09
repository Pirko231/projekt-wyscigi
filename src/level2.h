#pragma once

#include "level.h"

//poziom 2 - tutaj beda funkcje i kod dla poziomu 1. Dziedziczy klase 'Level'
class Level2 : public Level
{
public:
//do public jest taka sama zasada jak w klasie 'Level'

    Level2() = delete;
    Level2(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);

    //void handleEvents(sf::Event& _event);
    //void update();
    //void display();
private:
//calkowicie dla osoby ktora pracuje nad klasa.
    void resetLevel() override {}

};