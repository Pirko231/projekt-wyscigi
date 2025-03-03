#pragma once

#include <SFML/Graphics.hpp>

//klasa dziedziczy prywatnie sf::Sprite.
class Player : public sf::Drawable
{
public:
    Player();
    Player(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
    
    //zalozenie funkcji jest takie ze nacisniety zostal klawisz na klawiaturze
    //wiec nie musi juz sprawdzac czy nacisnieto klawisz
    void handleInput(sf::Event& _event);

    void setTexture(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->car, states);
    }

    sf::Sprite car;
    sf::Texture carTexture;
};