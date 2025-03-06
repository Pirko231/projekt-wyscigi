#include "car.h"
#include "util.h"

//includuj pliki w naglowkowym klasy a tutaj tylko plik klasy.h

Car::Car() :
    posX(50), posY(50)
{
    this->car.setPosition(posX, posY);

    this->car.setScale(1.f,1.f);
}

void Car::handleEvents(sf::Event& ev)
{
    pressed.check(ev);
}

void Car::move()
{
    if (pressed.w) {
        direction = 1;
        speed += stats.acceleration;
        speed = std::clamp(speed, 0.f, stats.maxSpeed);
    }
    if (pressed.s) {
        direction = -1;
        speed += stats.acceleration;
        speed = std::clamp(speed, 0.f, stats.maxSpeed);
    }
    if (pressed.a) {
        rotation = util::rem_euclid(rotation - stats.rotationSpeed, 360.f);
        rotation = std::clamp(rotation, 0.f, 360.f);
    }
    if (pressed.d) {
        rotation = util::rem_euclid(rotation + stats.rotationSpeed, 360.f);
    }
    car.setPosition(posX, posY);
    car.setRotation(rotation);
}

void Car::update(void)
{
    // FIXME: obliczyc gdzies deltatime naprawde
    float dt = 1.f / 60.f;
    float radians = rotation * (M_PI / 180); // bylo na matmie ;)
    float s = dt * speed;
    posX += s * direction * sin(radians);
    posY -= s * direction * cos(radians);
    speed -= s;
    if (speed < 0) speed = 0;

    this->move();
}

