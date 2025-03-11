#include "car.h"
#include "util.h"

#include <iostream>

//includuj pliki w naglowkowym klasy a tutaj tylko plik klasy.h

Car::Car() :
    posX(50), posY(50)
{
    this->car.setPosition(posX, posY);
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
    car.setPosition(posX, posY);
    car.setRotation(rotation);

}

void Car::reset()
{
    this->speed = 0;
    this->loops = 0;
    pressed.a = false;
    pressed.w = false;
    pressed.s = false;
    pressed.d = false;
}

void Car::manageCheckpoints(std::vector<bdr::CheckPoint>::iterator begin, std::vector<bdr::CheckPoint>::iterator end)
{
    if (this->getGlobalBounds().intersects(this->checkpoints->at(currentCheckpoint).getGlobalBounds()))
    {
        this->checkpoints->at(currentCheckpoint).activate();
        if (this->currentCheckpoint != (int)checkpoints->size() - 1)
            this->currentCheckpoint++;
        else
        {
            this->currentCheckpoint = 0;
            for (auto& it = begin; it != end; it++)
                it->reset();
            
            loops++;
        }
    }
}

void Car::update(void)
{
    actuallyHandleInput();

    // FIXME: obliczyc gdzies deltatime naprawde
    float dt = 1.f / 60.f;
    float radians = rotation * (M_PI / 180); // bylo na matmie ;)
    float s = dt * speed;
    posX += s * direction * sin(radians);
    posY -= s * direction * cos(radians);
    speed -= s;
    if (speed < 0) speed = 0;

    //tylko test potem wywlali sie pomiar czasu
    sf::Clock clock;
    for (auto& obj : *collisions)
        if (this->car.getGlobalBounds().intersects(obj->getGlobalBounds()))
            std::clog << "collision\n";
    sf::Time time {clock.getElapsedTime()};
    std::clog << time.asMicroseconds() << '\n';
    clock.restart();

    display();
}

