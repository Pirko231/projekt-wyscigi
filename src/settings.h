#pragma once

#include "buttons.h"

class Settings : public sf::Drawable
{
public:
    Settings(sf::Mouse* _mouse);

    operator bool() {return this->isTurnedOn;}
    //przypisuje do ustawien czy są obecnie wlaczane
    void operator=(bool _isOn) {this->isTurnedOn = _isOn;}

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->background, states);
        target.draw(this->x);
    }

    sf::Mouse* mouse;
    
    //jezeli prawda to ustawienia beda wyswietlane. Jezeli falsz to nie beda.
    bool isTurnedOn{false};

    //tlo ustawien
    sf::RectangleShape background;

    //przycisk X ktory opuszcza ustawienia
    btn::HoweredSpriteButton x;
};