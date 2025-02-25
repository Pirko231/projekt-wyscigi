#pragma once

#include "bodyFunction.h"

#include "buttons.h"
#include "raport.h"

class LevelSelection : public BodyFunction
{
public:
    LevelSelection() = delete;
    LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~LevelSelection();
private:
    //sekcja private jest calkowicie dla osoby ktora pracuje na funkcja

    //ustawienia
    btn::SpriteButton settings {btn::templates.getSettingsTemplate()};
};