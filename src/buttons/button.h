#pragma once

#include <SFML/Graphics.hpp>

namespace btn
{
    //klasa którą mogą dziedziczyc przyciski.
    //Pozwala uzywac przyciskow na zasadach polimorfizmu.
    class Button : public sf::Drawable
    {
    public:
        virtual bool manageHover(sf::Vector2i _mousePos, bool _clicked = false) = 0;

        virtual void setPosition(sf::Vector2f _pos) = 0;

        virtual void move(sf::Vector2f _pos) = 0;

    private:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    };
};