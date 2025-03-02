#pragma once

#include "button.h"

namespace btn
{

    class SpriteButton : public btn::Button
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

        sf::Vector2f getPosition() const {return this->sprite.getPosition();}

        void move(sf::Vector2f _pos) {this->sprite.move(_pos);}

        //restartuje parametry obiektu takie jak rozmiar oraz liczniki animacji
        void reset() {this->animation = this->maxAnimation; this->locked = false; this->setScale(this->defaultScale);}

        //skaluje obiekt na _scale
        //_maxScale - maksymalna skala podczas animacji. Kiedy nie ruszona zostanie sama obliczona
        //_speed - przyspiesza animacje
        void setScale(sf::Vector2f _scale, sf::Vector2f _maxScale = {0.f,0.f}, int _speed = 9) 
        {
            this->sprite.setScale(_scale); 
            this->defaultScale = _scale; 
            if(_maxScale == sf::Vector2f{0.f,0.f}) _maxScale = {_scale.x * 1.35f, _scale.y * 1.35f};
            this->maxScale = _maxScale;
            this->changeBy = {(_maxScale.x - _scale.x) / this->framerate * _speed, (_maxScale.y - _scale.y) / this->framerate * _speed};
        }

        //ustawia kąt rotacji na _angle
        void setRotation(float _angle) {this->sprite.setRotation(_angle);}
        
        //zwraca pozycje obiektu w globalnych koordynatach
        sf::FloatRect getGlobalBounds() const {return this->sprite.getGlobalBounds();}

        //zwraca pozycje obiektu w lokalnych koordynatach
        sf::FloatRect getLocalBounds() const {return this->sprite.getLocalBounds();}
        
        //sprawdza czy myszka jest na przycisku i reaguje na klikniecie.
        //_mousePos - pozycja myszki - zdobyc za pomoca mouse->getPosition(*this->window).
        //_clicked - mozna wprowadzic czy przycisk zostal klikniety. Domyslnie false.
        //zwraca true kiedy myszka znajduje sie na przycisku.
        bool manageHover(sf::Vector2i _mousePos, bool _clicked = false);
        
        //uzyc kiedy przycisk zostal klikniety
        //_maxAdditionalScale - okresla o ile wiekszy bedzie przycisk od maksymalnej skali po kliknieciu
        void startClickAnimation(sf::Vector2f _maxAdditionalScale = {0.07f, 0.07f});

        //wystarczy wywolac i samo sprawdzi czy ma robic animacje klikniecia
        //_lockedInput - mozna zablokowac dzialanie funkcji
        bool manage(bool _lockedInput = false);

        //zwraca true kiedy animacja jest skonczona. wprzeciwnym razie zwraca false
        bool isAnimationFinished() const {return this->animation <= 0;}
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->sprite, states);
        }

        //sprawdzic czy trwa animacja i kiedy trwa to uzyc
        void clicked();

        //zwraca true jesli trwa animacja. w przeciwnym razie zwraca false
        bool isAnimated() const {return this->animation < this->maxAnimation;}

        //przechowuje dane dla funkcji howered ktora bedzie usunieta i dana na private
        void howered_();

        //przechowuje dane dla funkcji unHowered ktora bedzie usunieta i dana na private
        void unHowered_();

        sf::Sprite sprite;

        //centruje animacje
        bool centre{false};
        
        //jezeli klikniety to blokuje powiekszanie i pomniejszanie
        bool locked{false};
        
        //klatki na sekunde
        int framerate{60};

        //ilosc maksymalnych klatek do zakonczenia animacji
        int maxAnimation{23};

        //ilosc klatek do zakonczenia animacji
        int animation{this->maxAnimation};

        //podstawowa skala obiektu
        sf::Vector2f defaultScale{1.f,1.f};

        //maksymalna skala obiektu podczas animacji
        sf::Vector2f maxScale{1.2f,1.2f};

        //o ile skala ma sie zmianiac na sekunde
        sf::Vector2f changeBy;

        //zapisuje skale po nacisnieciu przycisku
        sf::Vector2f previousScale;
    };

};