#include "checkpoint.h"

bdr::CheckPoint::CheckPoint(sf::Vector2f pos, sf::Vector2f size, float angle)
{
    this->object.setPosition(pos);
    this->object.setSize(size);
    this->object.setRotation(angle);
}

void bdr::CheckPoint::reset()
{
    this->activated = false;
}
