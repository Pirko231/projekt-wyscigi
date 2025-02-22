#pragma once
#include <SFML/Graphics.hpp>

namespace btn
{

    class SpriteButton : public sf::Drawable
    {
    public:
        //pamietaj aby nadac teksture
        SpriteButton() = default;

        //ustawia teksture (obraz) na _texture
        SpriteButton(const sf::Texture& _texture) {this->setTexture(_texture);}

        //ustawia pozycje na _pos
        //ustawia teksture (obraz) na _texture
        SpriteButton(sf::Vector2f _pos, const sf::Texture& _texture, sf::Vector2f _scale = {1.f,1.f}) {this->setPosition(_pos); this->setTexture(_texture); this->setScale(_scale);}

        //ustawia teksture na _texture
        void setTexture(const sf::Texture& _texture) {this->sprite.setTexture(_texture);}

        //ustawia pozycje na _pos
        void setPosition(sf::Vector2f _pos) {this->sprite.setPosition(_pos);}

        //skaluje obiekt na _scale
        void setScale(sf::Vector2f _scale) {this->sprite.setScale(_scale);}

        //zwraca hitbox obrazu aby mozna bylo porownac to z pozycja myszki
        sf::FloatRect getHitbox() {return this->hitbox.getGlobalBounds();}
        
        //jezeli jest najechany myszka (uzyj .getHitbox()) aby sprawdzic
        void howered();

        
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->sprite, states);
        }

        sf::Sprite sprite;
        sf::RectangleShape hitbox;
    };

};