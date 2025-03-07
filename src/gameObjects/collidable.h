#pragma once

#include <SFML/Graphics.hpp>

namespace bdr
{

    // abstrakcyjna klasa majaca na celu pozwolic przechowywanie wspolnego wektora
    // obiektow
    class Collidable : public sf::Drawable 
    {//trzeba bedzie wywalic to dziedziczenie potem
    public:
        virtual sf::Vector2f getPosition() const = 0;
        virtual sf::FloatRect getLocalBounds() const = 0;
        virtual sf::FloatRect getGlobalBounds() const = 0;
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
        
    };

};