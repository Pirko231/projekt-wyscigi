#pragma once

#include <SFML/Graphics.hpp>

//klasa dziedziczy prywatnie sf::Sprite.
class Player : public sf::RectangleShape
{
public:
    Player() {this->setSize({50.f, 50.f});}
private:

};