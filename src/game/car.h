#pragma once

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Window/Event.hpp"
#include "util.h"
#include "gameObjects.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <memory>
#include <optional>

//przechowuje dane o statysktychach auta. Definiowana w car.h
struct CarStats
{
    CarStats() {}
    CarStats(float _maxSpeed, float _acceleration, float _rotationSpeed)
    {
        this->maxSpeed = _maxSpeed;
        this->acceleration = _acceleration;
        this->rotationSpeed = _rotationSpeed;
    }

    void setFriction(float _friction) {this->friction = _friction;}

    //maksymalna predkosc samochodu. Wczesniej makro CAR_MAX_SPEED
    float maxSpeed{300};

    //przyspieszenie samochodu. Wczesniej makro CAR_ACCELERATION
    float acceleration{10};

    //predkosc rotacji samochodu. Wczesniej makro CAR_ROTATION_SPEED
    float rotationSpeed{5};

    // nie dotykac bardzo mozliwe ze bedzie gdzie indziej
    float friction{0.98f};
};

enum class Throttle {
    Break = -1,
    None = 0,
    Accelerate = 1,
};

enum class Steering {
    Left = -1,
    Straight = 0,
    Right = 1,
};

struct CarControls {
    CarControls() : throttle(Throttle::None), steering(Steering::Straight) {}
    CarControls(Throttle a, Steering b) : throttle(a), steering(b) {}

    Throttle throttle = Throttle::None;
    Steering steering = Steering::Straight;
};

class Car : public sf::Drawable
{
    friend class Cars;
public:
    //na public juz nic nie wrzucaj tylko na private lub protected
    //chyba ze chcesz dodac jakis konstruktor lub funkcje ktora wczytuje dane

    Car();

    Car(CarStats& _stats) : stats{_stats} {}

    Car(const sf::Texture& _carTexture, CarStats& _stats) : Car{_stats} {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
    //wywolac w funkcji update
    virtual void update();
    //wywolac w funkcji handleEvents
    virtual void handleEvents(sf::Event& _event) = 0;
    virtual void display();

    void setTexture(const sf::Texture& _carTexture, bool rescale = false) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture, rescale);}

    void setStats(const CarStats& _stats) {this->stats = _stats;}

    void setCollisions(const std::vector<std::unique_ptr<bdr::Collidable>>* _collisions) {this->collisions = _collisions;}

    void setPosition(sf::Vector2f pos) { this->position.x = pos.x; this->position.y = pos.y;}

    void setRotation(float angle) {this->rotation = angle;}

    void setFriction(float _friction) {this->stats.friction = _friction;}

    void setCheckPoints(std::vector<bdr::CheckPoint>* _checkpoints) {this->checkpoints = _checkpoints;}

    //resetuje predkosc oraz zapisane klikniecia klawiszy
    void reset();

    bool manageCheckpoints(std::vector<bdr::CheckPoint>::iterator begin, std::vector<bdr::CheckPoint>::iterator end, sf::Time currentTime);
    
    sf::Time getBestLap() const {return this->bestLap;}
    
    int getLaps() const {return this->laps;}
    
    sf::Vector2f getPosition() const {return this->car.getPosition();}

    float getRotation() const {return this->rotation;}

    sf::FloatRect getLocalBounds() const {return this->car.getLocalBounds();}

    sf::FloatRect getGlobalBounds() const {return this->car.getGlobalBounds();}

    std::optional<sf::FloatRect> collides() const;

    virtual ~Car() {}
private:
    //co tylko moze byc private zamiast protected powiino sie tutaj znalezc
    //wszystko co jest uniwersalne dla klasy gracz i bot powinno sie znalezc tutaj.
    //wszystko co mozna policzyc juz w tym miejscu niech tutaj zostanie policzone
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->car, states);
    }
    

    sf::Sprite car;
    sf::Texture carTexture;

    util::Vector2 position;
    float rotation = 0;
    float speed = 0;
    int direction = 1;
    bool carMoving = false;

    CarStats stats;
    
    int laps{0};

    const std::vector<std::unique_ptr<bdr::Collidable>>* collisions {nullptr};

    std::vector<bdr::CheckPoint>* checkpoints;

    int currentCheckpoint{0};

    bool firstLap{true};
    
    sf::Time bestLap;

    sf::Time previousTime;

    protected:
    //w tym miejscu mozna trzymac rzeczy ktore będą tez widoczne dla klas dziedziczacych
    util::Pressed pressed;
    CarControls controls;
};

