#pragma once

#include "border.h"

namespace bdr
{
    class Circle : public bdr::Border<sf::CircleShape>
    {
    public:
        Circle() = default;
        Circle(sf::CircleShape shape) : Border{shape} {}
    private:

    };
};