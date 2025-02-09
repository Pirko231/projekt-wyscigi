#ifndef LEVEL_SELECTION_H
#define LEVEL_SELECTION_H

#include "bodyFunction.h"

class LevelSelection : public BodyFunction
{
public:
    LevelSelection() = delete;
    LevelSelection(sf::RenderWindow* _window);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~LevelSelection();
private:
    //sekcja private jest calkowicie dla osoby ktora pracuje na funkcja
};

#endif