#include "settings.h"

Settings::Settings(sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->background.setFillColor(sf::Color{255, 24, 24});
}
