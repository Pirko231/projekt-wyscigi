#include "howeredSpriteButton.h"

bool btn::HoweredSpriteButton::manageHover(sf::Vector2i _mousePos, bool _clicked)
{
    if (this->current.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        if (_clicked);
            //this->startClickAnimation();
        else
            this->howered_();
        return true;
    }
    else
        this->unHowered_();

    return false;
}

void btn::HoweredSpriteButton::howered_()
{
    this->current.setTexture(this->howeredTexture);
}

void btn::HoweredSpriteButton::unHowered_()
{
    this->current.setTexture(this->unHoweredTexture);
}
