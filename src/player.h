#pragma once

#include <SFML/Graphics.hpp>

//klasa dziedziczy prywatnie sf::Sprite.
class Player : public sf::Drawable
{
public:
    Player();
    Player(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
    void handleInput(sf::Event& _event);
    void setTexture(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
    void update(void);

    double posX = 0;
    double posY = 0;
    double rotation = 0;
    double speed = 0;
    int direction = 1;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->car, states);
    }

    sf::Sprite car;
    sf::Texture carTexture;
};
