#include "player.h"

Player::Player()
{
    this->car.setPosition(50.f, 50.f);

    this->car.setScale(1.f,1.f);
}

void Player::handleInput(sf::Event &_event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->car.move({0.f, -2.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->car.move({0.f, 2.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->car.move({-2.f, 0.f});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->car.move({2.f, 0.f});
}
