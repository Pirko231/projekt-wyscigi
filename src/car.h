#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

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
    //maksymalna predkosc samochodu. Wczesniej makro CAR_MAX_SPEED
    float maxSpeed{100};

    //przyspieszenie samochodu. Wczesniej makro CAR_ACCELERATION
    float acceleration{10};

    //predkosc rotacji samochodu. Wczesniej makro CAR_ROTATION_SPEED
    float rotationSpeed{5};
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
    virtual void handleEvents(sf::Event& _event);

    void setTexture(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}

    void setStats(CarStats& _stats) {this->stats = _stats;}

    sf::Vector2f getPosition() const {return this->car.getPosition();}

    float getRotation() const {return this->rotation;}

    sf::FloatRect getLocalBounds() const {return this->car.getLocalBounds();}

    sf::FloatRect getGlobalBounds() const {return this->car.getGlobalBounds();}
private:
    //co tylko moze byc private zamiast protected powiino sie tutaj znalezc
    //wszystko co jest uniwersalne dla klasy gracz i bot powinno sie znalezc tutaj.
    //wszystko co mozna policzyc juz w tym miejscu niech tutaj zostanie policzone
    
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->car, states);
    }

    //porusza obiekt w zaleznosci od wattosci zmiennch xPressed
    void move();

    bool wPressed{false};
    bool sPressed{false};
    bool aPressed{false};
    bool dPressed{false};

    sf::Sprite car;
    sf::Texture carTexture;

    float posX = 0;
    float posY = 0;
    float rotation = 0;
    float speed = 0;
    int direction = 1;

    CarStats stats;
    //zamkniemy to w strukturze CarStats
    
    /*//maksymalna predkosc samochodu. Wczesniej makro CAR_MAX_SPEED
    double maxSpeed{100};

    //przyspieszenie samochodu. Wczesniej makro CAR_ACCELERATION
    double acceleration{10};

    //predkosc rotacji samochodu. Wczesniej makro CAR_ROTATION_SPEED
    double rotationSpeed{5};*/

    protected:
    //w tym miejscu mozna trzymac rzeczy ktore będą tez widoczne dla klas dziedziczacych
};

