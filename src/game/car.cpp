#include "car.h"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "util.h"

#include <iostream>

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

    if (pressed.a == pressed.d) {
        controls.steering = Steering::Straight;
    } else if (pressed.a) {
        controls.steering = Steering::Left;
    } else if (pressed.d) {
        controls.steering = Steering::Right;
    }
    if (pressed.w == pressed.s) {
        controls.throttle = Throttle::None;
    } else if (pressed.w) {
        controls.throttle = Throttle::Accelerate;
    } else if (pressed.s) {
        controls.throttle = Throttle::Break;
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
    this->laps = 0;
    this->currentCheckpoint = 0;
    this->firstLap = true;
    pressed.a = false;
    pressed.w = false;
    pressed.s = false;
    pressed.d = false;
}

bool Car::manageCheckpoints(std::vector<bdr::CheckPoint>::iterator begin, std::vector<bdr::CheckPoint>::iterator end, sf::Time currentTime)
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
            
            laps++;
            if (currentTime - previousTime < this->bestLap || this->firstLap)
            {
                this->bestLap = currentTime - previousTime;
                this->firstLap = false;
            }
            previousTime = currentTime; 
            return true;
        }
    }
    return false;
}

bool Car::collides() const
{
    //tylko test potem wywlali sie pomiar czasu
    sf::Clock clock;
    for (auto& obj : *collisions) {
        if (this->car.getGlobalBounds().intersects(obj->getGlobalBounds())) {
            return true;
        }
    }
    sf::Time time {clock.getElapsedTime()};
    std::clog << time.asMicroseconds() << '\n' << speed << '\n';

    return false;
}

void Car::update(void)
{
    if (controls.throttle == Throttle::Accelerate) {
        direction = 1;
        speed += stats.acceleration;
        speed = std::clamp(speed, 0.f, stats.maxSpeed);
    }
    if (controls.throttle == Throttle::Break) {
        direction = -1;
        speed += stats.acceleration;
        speed = std::clamp(speed, 0.f, stats.maxSpeed);
    }
    if (carMoving) {
        if (controls.steering == Steering::Left) {
            rotation = util::rem_euclid(rotation - stats.rotationSpeed, 360.f);
        }
        if (controls.steering == Steering::Right) {
            rotation = util::rem_euclid(rotation + stats.rotationSpeed, 360.f);
        }
    }

    // FIXME: obliczyc gdzies deltatime naprawde
    float dt = 1.f / 60.f;
    float radians = util::radians(rotation);
    util::Vector2 forwards = { sinf(radians), -cosf(radians) };
    util::Vector2 velocity = forwards * direction * speed * dt;

    if (this->collides()) {
        velocity = -velocity * 0.5;
    }

    position += velocity;



    speed *= stats.friction;

    if (speed > 10 && !carMoving) {
        carMoving = true;
    }
    if (speed < 7 && carMoving) {
        speed = 0;
        carMoving = false;
    }

    display();
}
