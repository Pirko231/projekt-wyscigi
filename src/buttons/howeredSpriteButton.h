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
        {this->howeredTexture = _howered; this->unHoweredTexture = _unHowered; this->current.setTexture(_unHowered);}

        //ustawia skale na _scale
        void setScale(sf::Vector2f _scale) {this->current.setScale(_scale);}

        //zwraca pozycje obiektu w globalnych koordynatach
        sf::FloatRect getGlobalBounds() const {return this->current.getGlobalBounds();}

        //zwraca pozycje obiektu w lokalnych koordynatach
        sf::FloatRect getLocalBounds() const {return this->current.getLocalBounds();}

        //sprawdza czy myszka jest na przycisku i reaguje na klikniecie.
        //_mousePos - pozycja myszki - zdobyc za pomoca mouse->getPosition(*this->window).
        //_clicked - mozna wprowadzic czy przycisk zostal klikniety. Domyslnie false.
        //zwraca true kiedy myszka znajduje sie na przycisku.
        bool manageHover(sf::Vector2i _mousePos, bool _clicked = false);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->current, states);
        }

        void howered_();

        void unHowered_();
        
        sf::Sprite current;

        //
        sf::Texture unHoweredTexture;

        sf::Texture howeredTexture;
    };
};