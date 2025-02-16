#pragma once

#include "bodyFunction.h"

class LevelSelection : public BodyFunction
{
public:
    LevelSelection() = delete;
    LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~LevelSelection();
private:
    //sekcja private jest calkowicie dla osoby ktora pracuje na funkcja
};