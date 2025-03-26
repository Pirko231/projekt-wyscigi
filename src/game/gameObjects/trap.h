#pragma once

#include "collidable.h"

namespace bdr
{
    //klasa ktora ma być bazą do dziedziczenia wszystkich pulapek
    //oferuje implementacje funkcji wirtualnych i przechowuje obiekt sf::Sprite i jego teksture
    class Trap : public bdr::Collidable, public sf::Drawable
    {
    public:
        sf::Vector2f getPosition() const override {return this->sprite.getPosition();}
        sf::FloatRect getLocalBounds() const override {return this->sprite.getLocalBounds();}
        sf::FloatRect getGlobalBounds() const override {return this->sprite.getGlobalBounds();}
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->sprite, states);
        }
        sf::Sprite sprite;
        sf::Texture spriteTexture;
    };
};