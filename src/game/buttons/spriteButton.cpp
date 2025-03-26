#include "spriteButton.h"

void btn::SpriteButton::startClickAnimation(sf::Vector2f _maxAdditionalScale)
{
    this->locked = true;
    this->animation--;
    this->previousScale = this->sprite.getScale();
    this->sprite.setScale({(this->maxScale.x + _maxAdditionalScale.x), (this->maxScale.y + _maxAdditionalScale.y)});

    this->sprite.setPosition({this->sprite.getPosition().x + this->sprite.getScale().x - this->previousScale.x, this->sprite.getPosition().y + this->sprite.getScale().y - this->previousScale.y});
}

bool btn::SpriteButton::manageHover(sf::Vector2i _mousePos, bool _clicked)
{
    if (this->sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        if (_clicked)
            this->startClickAnimation();
        else
            this->howered_();
        return true;
    }
    else
        this->unHowered_();

    return false;
}

void btn::SpriteButton::clicked()
{
    if (this->animation == this->maxAnimation / 2)
    {  
        sf::Vector2f scale{this->sprite.getScale().x - this->previousScale.x, this->sprite.getScale().y - this->previousScale.y};
        this->sprite.setScale(this->previousScale);
        this->sprite.setPosition({this->sprite.getPosition().x + scale.x}, this->sprite.getPosition().y + scale.y);
    }
    
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

void btn::SpriteButton::howered_()
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

void btn::SpriteButton::unHowered_()
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
