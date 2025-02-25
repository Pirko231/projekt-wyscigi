#pragma once

#include <SFML/Graphics.hpp>

namespace btn
{
    class HoweredSpriteButton : public sf::Drawable
    {
    public:
        HoweredSpriteButton() = default;

        //ustawia teksture na _howered i teksture po najechaniu na _unHowered
        HoweredSpriteButton(const sf::Texture& _howered, const sf::Texture& _unHowered) {this->setTextures(_howered, _unHowered);}

        //ustawia pozycje na _pos
        void setPosition(sf::Vector2f _pos) {this->current.setPosition(_pos);}

        //ustawia teksture na _howered i teksture po najechaniu na _unHowered
        void setTextures(const sf::Texture& _howered, const sf::Texture& _unHowered)
        {this->howeredTexture = _howered; this->unHoweredTexture = _unHowered;}

        //ustawia skale na _scale
        void setScale(sf::Vector2f _scale) {this->current.setScale(_scale);}

        //zwraca hitbox obiektu. Uzyc aby sprawdzic czy nie zostal najechany/ klikniety
        sf::FloatRect getHitbox() {return this->current.getGlobalBounds();}
    
        //uzyc kiedy myszka na niego najechala. sprawdz uzywajac .getHitbox
        void howered();

        //uzyc kiedy wiadomo ze myszka na niego nie najechala. sprawdz uzywajac .getHitbox
        void unHowered();
    
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->current, states);
        }
        
        sf::Sprite current;

        //
        sf::Texture unHoweredTexture;

        sf::Texture howeredTexture;
    };
};