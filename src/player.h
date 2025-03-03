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

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->car, states);
    }

    //reaguje na zmienne bool i porusza obiekt
    void move();

    bool wPressed{false};
    bool sPressed{false};
    bool aPressed{false};
    bool dPressed{false};

    sf::Sprite car;
    sf::Texture carTexture;

    double posX = 0;
    double posY = 0;
    double rotation = 0;
    double speed = 0;
    int direction = 1;

    //maksymalna predkosc samochodu. Wczesniej makro CAR_MAX_SPEED
    double maxSpeed{100};

    //przyspieszenie samochodu. Wczesniej makro CAR_ACCELERATION
    double acceleration{10};

    //predkosc rotacji samochodu. Wczesniej makro CAR_ROTATION_SPEED
    double rotationSpeed{5};
};
