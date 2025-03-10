#include "car.h"
#include "util.h"

//includuj pliki w naglowkowym klasy a tutaj tylko plik klasy.h

Car::Car() :
    position(50, 50)
{
    this->car.setPosition(position.x, position.y);
    this->car.setScale(0.4f,0.4f);
}

void Car::handleEvents(sf::Event& ev)
{
    pressed.check(ev);
}

void Car::actuallyHandleInput()
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
    }
    if (pressed.d) {
        rotation = util::rem_euclid(rotation + stats.rotationSpeed, 360.f);
    }
}

void Car::display()
{
    auto lb = car.getLocalBounds();

    car.setOrigin(lb.width / 2.f, lb.height / 2.f);
    car.setPosition(position.x, position.y);
    car.setRotation(rotation);

}

void Car::reset()
{
    this->speed = 0;
    pressed.a = false;
    pressed.w = false;
    pressed.s = false;
    pressed.d = false;
}

void Car::update(void)
{
    actuallyHandleInput();

    // FIXME: obliczyc gdzies deltatime naprawde
    float dt = 1.f / 60.f;
    float radians = util::toRadians(rotation);
    float s = dt * speed;
    position.x += s * direction * sin(radians);
    position.y -= s * direction * cos(radians);
    speed -= s;
    if (speed < 0) speed = 0;

    display();
}

