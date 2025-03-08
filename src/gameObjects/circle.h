#pragma once

#include "border.h"

namespace bdr
{
    class Circle : public bdr::Border<sf::CircleShape>
    {
    public:
        Circle() = default;
        Circle(sf::CircleShape shape) : Border{shape} {}
        Circle(sf::Vector2f _pos, float _radius) {this->object.setRadius(_radius); this->object.setPosition(_pos);}
    private:

    };
};