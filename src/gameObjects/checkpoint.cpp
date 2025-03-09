#include "checkpoint.h"

bdr::CheckPoint::CheckPoint(sf::Vector2f pos, sf::Vector2f size)
{
    this->object.setPosition(pos);
    this->object.setSize(size);
}

void bdr::CheckPoint::reset()
{
    this->activated = false;
}
