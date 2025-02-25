#include "settings.h"

Settings::Settings(sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->background.setFillColor(sf::Color{255, 24, 24});
}

void Settings::handleEvents(sf::Event &_event)
{
}

void Settings::update()
{
}

void Settings::display()
{
}
