#pragma once

#include "border.h"

namespace bdr
{
    class CheckPoint : public bdr::Border<sf::RectangleShape>
    {
    public:
        CheckPoint(sf::Vector2f pos, sf::Vector2f size, float angle = 0);
        //aktywuje checkpoint (od teraz zostal juz przejechany)
        void activate() {this->activated = true;}
        //resetuje checkpoint czyli ustawia ze nie zostal jeszcze aktywowany
        void reset();
        //zwroci true kiedy checkpoint zostal aktywowany
        bool isActive() const {return activated;}
    private:
        bool activated{false};
    };
};