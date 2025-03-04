#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

class Car : public sf::Drawable
{
public:
    //na public juz nic nie wrzucaj tylko na private lub protected
    //chyba ze chcesz dodac jakis konstruktor lub funkcje ktora wczytuje dane
    
    Car();
    
    Car(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
    //wywolac w funkcji update
    virtual void update();
    //wywolac w funkcji handleEvents
    virtual void handleEvents(sf::Event& _event);

    void setTexture(const sf::Texture& _carTexture) {this->carTexture = _carTexture; this->car.setTexture(this->carTexture);}
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

    double posX = 0;
    double posY = 0;
    double rotation = 0;
    double speed = 0;
    int direction = 1;

    //maksymalna predkosc samochodu. Wczesniej makro CAR_MAX_SPEED
    double maxSpeed{100};

    //przyspieszenie samochodu. Wczesniej makro CAR_ACCELERATION
    double acceleration{10};

    //predkosc rotacji samochodu. Wczesniej makro CAR_ROTATION_SPEED
    double rotationSpeed{5};

    protected:
    //w tym miejscu mozna trzymac rzeczy ktore będą tez widoczne dla klas dziedziczacych
};