#pragma once

#include "collidable.h"

namespace bdr
{

    // klasa ktora przechowuje szablon dla klas ktore mogą
    // byc uzyte do sprawdzania kolizji
    template <typename T>
    class Border : public Collidable
    {
    public:
        Border() = default;
        Border(T obj) { this->object = obj; }
        sf::Vector2f getPosition() const { return object.getPosition(); }
        sf::FloatRect getLocalBounds() const { return object.getLocalBounds(); }
        sf::FloatRect getGlobalBounds() const { return object.getGlobalBounds(); }

    private:
        // obiekt ktorego sprawdzamy kolizje
        T object;

        //rysowanko
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->object, states);
        }
    };

};
