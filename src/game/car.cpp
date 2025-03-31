#include "car.h"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"
#include "util.h"

#include <cstdlib>
#include <iostream>
#include <optional>

//includuj pliki w naglowkowym klasy a tutaj tylko plik klasy.h

Car::Car() :
    position(50, 50)
{
    this->car.setPosition(position.x, position.y);
    this->car.setScale(0.4f,0.4f);
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
    this->previousTime = sf::seconds(0.f);
    this->bestLap = sf::seconds(0.f);
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

std::optional<sf::FloatRect> Car::collides() const
{
    for (auto& obj : *collisions) {
        if (this->car.getGlobalBounds().intersects(obj->getGlobalBounds())) {
            return obj->getGlobalBounds();
        }
    }

    return {};
}

sf::FloatRect getCollision(sf::FloatRect r1, sf::FloatRect r2)
{
    sf::FloatRect overlap = {};

    float left = (r1.left > r2.left)? r1.left : r2.left;
    float right1 = r1.left + r1.width;
    float right2 = r2.left + r2.width;
    float right = (right1 < right2)? right1 : right2;
    float top = (r1.top > r2.top)? r1.top : r2.top;
    float bottom1 = r1.top + r1.height;
    float bottom2 = r2.top + r2.height;
    float bottom = (bottom1 < bottom2)? bottom1 : bottom2;

    if ((left < right) && (top < bottom))
    {
        overlap.left = left;
        overlap.top = top;
        overlap.width = right - left;
        overlap.height = bottom - top;
    }

    return overlap;
}

void Car::update(void)
{
    if (controls.throttle == Throttle::Accelerate) {
        speed += stats.acceleration;
        if (speed > stats.maxSpeed)
            speed = stats.maxSpeed;
    }
    if (controls.throttle == Throttle::Break) {
        speed -= stats.acceleration;
        if (speed < -stats.maxSpeed)
            speed = -stats.maxSpeed;
    }
    if (carMoving) {
        float rspeed = std::clamp(std::abs(speed / 100.f), 0.f, 1.f);
         if (controls.steering == Steering::Left) {
            rotation = util::rem_euclid(rotation - stats.rotationSpeed * rspeed, 360.f);
         }
         if (controls.steering == Steering::Right) {
            rotation = util::rem_euclid(rotation + stats.rotationSpeed * rspeed, 360.f);
         }
    }

    float radians = util::radians(rotation);
    util::Vector2 forwards = { sinf(radians), -cosf(radians) };
    speed *= stats.friction;
    util::Vector2 velocity = forwards * speed * util::dt;
    position += velocity;
    

    std::optional<sf::FloatRect> maybe = collides();
    if (maybe.has_value()) {
        auto hitbox = getGlobalBounds();
        auto wall = *maybe;
        auto overlap = getCollision(hitbox, wall);

        if (overlap.width < overlap.height) {
            if (hitbox.left < wall.left) {
                position.x -= overlap.width;
            } else {
                position.x += overlap.width;
            }
        } else {
            if (hitbox.top < wall.top) {
                position.y -= overlap.height;
            } else {
                position.y += overlap.height;
            }
        }
    }

    if (std::abs(speed) > 10 && !carMoving) {
        carMoving = true;
    }
    if (std::abs(speed) < 7 && carMoving) {
        speed = 0;
        carMoving = false;
    }

    display();
}
