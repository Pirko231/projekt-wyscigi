#pragma once

#include "border.h"

namespace bdr
{
    class Rectangle : public bdr::Border<sf::RectangleShape>
    {
    public:
        Rectangle() = default;
        Rectangle(sf::RectangleShape shape) : Border{shape} {}
        Rectangle(sf::Vector2f _pos, sf::Vector2f _size) : Border{_pos, _size} {}
    };
};