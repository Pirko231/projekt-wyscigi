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
        //_maxScale - maksymalna skala podczas animacji. Kiedy nie ruszona zostanie sama obliczona
        void setScale(sf::Vector2f _scale, sf::Vector2f _maxScale = {0.f,0.f}) {this->sprite.setScale(_scale); this->defaultScale = _scale; if(_maxScale == sf::Vector2f{0.f,0.f}) this->maxScale = {_scale.x * 1.3f, _scale.y * 1.3f}; else this->maxScale = _maxScale;}

        //ustawia kąt rotacji na _angle
        void setRotation(float _angle) {this->sprite.setRotation(_angle);}
        
        //zwraca hitbox obrazu aby mozna bylo porownac to z pozycja myszki
        sf::FloatRect getHitbox() {return this->hitbox.getGlobalBounds();}
        
        //uzyc kiedy przycisk zostal klikniety
        void clicked();
        
        //jezeli jest najechany myszka (uzyj .getHitbox()) aby sprawdzic
        void howered();

        
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->sprite, states);
        }

        sf::Sprite sprite;
        sf::RectangleShape hitbox;

        //podstawowa skala obiektu
        sf::Vector2f defaultScale{1.f,1.f};

        //maksymalna skala obiektu podczas animacji
        sf::Vector2f maxScale{1.2f,1.2f};

        //o ile skala ma sie zmianiac na sekunde
        float changeBy;

    };

};