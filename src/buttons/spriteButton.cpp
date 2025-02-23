#include "spriteButton.h"

void btn::SpriteButton::startClickAnimation(sf::Vector2f _maxAdditionalScale)
{
    this->locked = true;
    this->animation--;
    this->previousScale = this->sprite.getScale();
    this->sprite.setScale({(this->maxScale.x + _maxAdditionalScale.x), (this->maxScale.y + _maxAdditionalScale.y)});
}

void btn::SpriteButton::clicked()
{
    if (this->animation == this->maxAnimation / 2)    
        this->sprite.setScale(this->previousScale);
    
    this->animation--;
}

bool btn::SpriteButton::manage(bool _lockedInput)
{

    if (_lockedInput)
        return false;

    if (this->isAnimated()) 
        this->clicked();

    if (this->isAnimationFinished())
        return true;
    
    return false;
}

void btn::SpriteButton::howered()
{
    if (this->locked)
        return;
    
    if (this->sprite.getScale().x < this->maxScale.x && this->sprite.getScale().y < this->maxScale.y)
    {
        this->sprite.setScale(this->sprite.getScale() + this->changeBy);
        //this->hitBox.setSize({this->sprite.getLocalBounds().width, static_cast<float>(this->sprite.getLocalBounds().height * 1.35)});
    }
    else
    {
        this->sprite.setScale(this->maxScale);
        //this->hitBox.setSize({this->sprite.getLocalBounds().width, static_cast<float>(this->sprite.getLocalBounds().height * 1.35)});
    }
}

void btn::SpriteButton::unHowered()
{
    if (this->locked)
        return;

    if (this->sprite.getScale().x > this->defaultScale.x && this->sprite.getScale().y > this->defaultScale.y)
    {
        this->sprite.setScale(this->sprite.getScale() - this->changeBy);
        //this->hitBox.setSize({this->sprite.getLocalBounds().width, this->sprite.getLocalBounds().height * 1.35f});
    }
    else
    {
        this->sprite.setScale(this->defaultScale);
        //this->hitBox.setSize({this->sprite.getLocalBounds().width, this->sprite.getLocalBounds().height * 1.35f});
    }
}
