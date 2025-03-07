#pragma once

#include "border.h"

namespace bdr
{
    class Rectangle : public bdr::Border<sf::RectangleShape>
    {
    public:
        Rectangle() = default;
        Rectangle(sf::RectangleShape shape) : Border{shape} {}
    };
};