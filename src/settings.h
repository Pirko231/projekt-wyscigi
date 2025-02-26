#pragma once

#include "buttons.h"

class Settings
{
public:
    Settings(sf::RenderWindow* _window, sf::Mouse* _mouse);

    void handleEvents(sf::Event& _event);

    void update();

    void display();

    operator bool() {return this->isTurnedOn;}
    //przypisuje do ustawien czy są obecnie wlaczane
    void operator=(bool _isOn) {this->isTurnedOn = _isOn;}

private:
    /*void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->background, states);
        target.draw(this->x);

        //testy
        target.draw(this->bt, states);
    }*/

    sf::RenderWindow* window;

    sf::Mouse* mouse;
    
    //jezeli prawda to ustawienia beda wyswietlane. Jezeli falsz to nie beda.
    bool isTurnedOn{false};

    //tlo ustawien
    sf::RectangleShape background;

    //przycisk X ktory opuszcza ustawienia
    btn::HoweredSpriteButton x {btn::templates.getXTemplate()};
};