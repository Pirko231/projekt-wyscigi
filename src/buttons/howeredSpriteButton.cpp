#include "howeredSpriteButton.h"

void btn::HoweredSpriteButton::howered()
{
    this->current.setTexture(this->howeredTexture);
}

void btn::HoweredSpriteButton::unHowered()
{
    this->current.setTexture(this->unHoweredTexture);
}
