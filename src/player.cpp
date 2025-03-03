#include <algorithm>
#include <cmath>

#include "player.h"
#include "SFML/Window/Keyboard.hpp"

// FIXME: czy to jest najlepszy sposob ? nie jestem pewien

//dodalem w klasie na private te zmienne, potem będą zalezne od rodzaju samochodu
//mam pomysl na zrobienie czegos w stylu globalnej struktury ktora bedzie dzialala jak 'garaz'
//i klasy typu level będą pozyczaly tylko wskaznik od tego 'garazu' i uzywala jego aut.
//garaz wczytywalby wtedy tekstury, a komunikacja odbywalaby sie za pomocą
//settings->getStartingData()->zmienna

/*#define CAR_MAX_SPEED 100.0
#define CAR_ACCELERATION 10.0
#define CAR_ROTATION_SPEED 5.0*/

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

    //przenioslem do funkcji move a tutaj są ustawiane tylko zmienne bool
    if (_event.type == sf::Event::KeyPressed)
    {
        if (_event.key.code == sf::Keyboard::W)
        {
            wPressed = true;
        }
        if (_event.key.code == sf::Keyboard::S)
        {
            sPressed = true;
        }
        if (_event.key.code == sf::Keyboard::A)
        {
            aPressed = true;
        }
        if (_event.key.code == sf::Keyboard::D)
        {
            dPressed = true;
        }
    }

    if (_event.type == sf::Event::KeyReleased)
    {
        if (_event.key.code == sf::Keyboard::W)
            wPressed = false;
        
        if (_event.key.code == sf::Keyboard::S)
            sPressed = false;
        
        if (_event.key.code == sf::Keyboard::A)
            aPressed = false;
        
        if (_event.key.code == sf::Keyboard::D)
            dPressed = false;
        
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

    this->move();
    // smieszne 
    // car.rotate(rotation);
}

void Player::move()
{
    if (wPressed)
    {
        direction = 1;
        speed += acceleration;
        speed = std::clamp(speed, 0.0, maxSpeed);
    }
    if (sPressed)
    {
        direction = -1;
        speed += acceleration;
        speed = std::clamp(speed, 0.0, maxSpeed);
    }
    if (aPressed)
    {
        rotation = eucl_mod(rotation - rotationSpeed, 360.0);
        rotation = std::clamp(rotation, 0.0, 360.0);
    }
    if (dPressed)
    {
        rotation = eucl_mod(rotation + rotationSpeed, 360.0);
    }
    car.setPosition(posX, posY);
    car.setRotation(rotation);
}
