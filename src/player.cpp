#include <algorithm>
#include <cmath>

#include "player.h"
#include "SFML/Window/Keyboard.hpp"

// FIXME: czy to jest najlepszy sposob ? nie jestem pewien
#define CAR_MAX_SPEED 100.0
#define CAR_ACCELERATION 10.0
#define CAR_ROTATION_SPEED 5.0

// mozna by zrobic folder utils/ gdzie takie rozne pomocne funkcje moga byc
double eucl_mod(double x, double y)
{
    double ret = fmod(x, y);
    if (ret < 0) ret = ret + fabs(y);
    return ret;
}


Player::Player() :
    posX(50), posY(50)
{
    this->car.setPosition(posX, posY);

    this->car.setScale(1.f,1.f);
}

void Player::handleInput(sf::Event &_event)
{
    // FIXME: sfml robi jakies costam ze trzeba trch przytrzymac ?? idk
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        direction = 1;
        speed += CAR_ACCELERATION;
        speed = std::clamp(speed, 0.0, CAR_MAX_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction = -1;
        speed += CAR_ACCELERATION;
        speed = std::clamp(speed, 0.0, CAR_MAX_SPEED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotation = eucl_mod(rotation - CAR_ROTATION_SPEED, 360.0);
        rotation = std::clamp(rotation, 0.0, 360.0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotation = eucl_mod(rotation + CAR_ROTATION_SPEED, 360.0);
    }
}

void Player::update(void)
{
    // FIXME: obliczyc gdzies deltatime naprawde
    double dt = 1.0/60.0;
    double radians = rotation * (M_PI / 180); // bylo na matmie ;)
    double s = dt * speed;
    posX += s * direction * sin(radians);
    posY -= s * direction * cos(radians);
    speed -= s;
    if (speed < 0) speed = 0;

    // update teksture 💔
    // jakoms funkcje na to moze? moze... display ?
    // Player : BodyFunction those who know 💀💀💀

    car.setPosition(posX, posY);
    car.setRotation(rotation);
    // smieszne 
    // car.rotate(rotation);
}
