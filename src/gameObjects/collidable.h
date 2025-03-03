#pragma once

#include <SFML/Graphics.hpp>

//abstrakcyjna klasa majaca na celu pozwolic przechowywanie wspolnego wektora
//obiektow
class Collidable
{
public:
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::FloatRect getLocalBounds() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
};