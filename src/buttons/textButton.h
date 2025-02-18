#pragma once

#include <SFML/Graphics.hpp>

namespace btn
{
    class TextButton : public sf::Drawable
    {
    public:
        //pamietaj aby nadac czcionke
        TextButton() = default;
        //ustawia przycisk na pozycji 0.f,0.f
        //nadaje czcionke _font
        TextButton(sf::Font& _font) {this->text.setFont(_font);}

        //ustawia obiekt na pozycji _pos
        //nadaje czcionke _font
        //ustawia rozmiar czcionki na _characterSize
        TextButton(sf::Vector2f _pos, const sf::Font& _font, unsigned int _characterSize);
    
        //ustawia obiekt na pozycji _pos
        //ustawia rozmiar czcionki na _characterSize
        //pamietaj aby dodac czcionke bo inaczej nie dziala
        TextButton(sf::Vector2f _pos, unsigned int _characterSize);

        //zwraca hitbox przycisku, mozna sprawdzic czy przycisk jest najechany
        sf::FloatRect getHitbox() const {return this->hitBox.getGlobalBounds();}
    
        //ustawia czcionke na _font
        void setFont(const sf::Font& _font) {this->text.setFont(_font);}

        //ustawia zawartosc tekstu na _string
        void setString(const sf::String& _string) {this->text.setString(_string); this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});}
        
        //ustawia pozycje na _pos
        void setPosition(sf::Vector2f _pos) {this->text.setPosition(_pos); this->hitBox.setPosition(_pos);}
        
        //ustawia kolor tekstu na _color
        void setFillColor(const sf::Color& _color) {this->text.setFillColor(_color);}
        
        //kiedy klikniety (sprawdz uzywajac .getHitbox())
        //to rozpoczyna sie animacja klikniecia
        void clicked();
        
        //kiedy najechany (sprawdz uzywajac .getHitbox())
        //to zaczyna sie animacja przycisku
        void howered();

        //kiedy przestal byc najechany (sprawdz uzywajac .getHitbox())
        //to zaczyna sie animacja przycisku w druga strone
        void unHowered();
    private:
            //rysuje obiekt.
            //uzyj window->draw(TextButton) aby uzyc
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override
            {
                // You can draw other high-level objects
                target.draw(this->text, states);
            }

        //tekst
        sf::Text text;

        // hitbox tego przycisku
        sf::RectangleShape hitBox;

        // framerate jako 60 fps
        int framerate{60};

        // zawsze podczas animacji czcionka wraca do tego rozmiaru
        unsigned int defaultCharacterSize{30};

        // maksmalny rozmiar jaki osiaga czcionka podczas animacji
        unsigned int maxCharacterSize{42};

        // wyliczone w konstruktorze
        float changeSizeBy{0.2f};
    };

};