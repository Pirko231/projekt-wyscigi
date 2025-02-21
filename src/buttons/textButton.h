#pragma once

#include <SFML/Graphics.hpp>

namespace btn
{
    class TextButton : public sf::Drawable
    {
    public:
        //pamietaj aby nadac czcionke
        TextButton(unsigned int _characterSize = 30);

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

        //restartuje rozmiar obiektu.
        //uzywac przy zmianie okna
        void reset() {this->text.setCharacterSize(this->defaultCharacterSize); this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});}

        //rozpoczyna animacje przycisku
        void startClickAnimation() {this->clicked();}
        
        //sprawdza czy trwa animacja klikniecia
        bool isAnimated() {if (this->animation < this->maxAnimation) return true; return false;}

        //zwraca ilosc klatek kiedy skonczy sie animacja
        bool isAnimationFinished() {if (this->animation <= 0) {this->animation = this->maxAnimation; return true;} return false;}

        //ustawia dane dotyczace animacji
        //_length - ilosc klatek w ktorych bedzie dziala sie animacja
        //_perSecond - na ile klatek zmienia sie kolor
        void setAnimation(unsigned int _length = 40, unsigned int _perSecond = 5) {this->animation = _length; this->maxAnimation = _length; this->perSecond = _perSecond;}
    
        //ustawia czcionke na _font
        void setFont(const sf::Font& _font) {this->text.setFont(_font);}

        //ustawia zawartosc tekstu na _string
        void setString(const sf::String& _string);
        
        //ustawia pozycje na _pos
        void setPosition(sf::Vector2f _pos) {this->text.setPosition(_pos); this->hitBox.setPosition(_pos);}
        
        //ustawia kolor tekstu na _color
        //ustawia kolor animacji na _animationColor
        void setFillColor(const sf::Color& _color, const sf::Color& _animationColor = sf::Color{192, 190, 190}) {this->text.setFillColor(_color); this->baseColor = _color; this->animationColor = _animationColor;}

        //ustawia rozmiar czcionki i maksymalnej czcionki
        //_characterSize - rozmiar czcionki
        //_maxCharacterSize - rozmiar maksymalnego powiekszenia.
        //nie trzeba wprowadzac _maxCharacterSize bo zostanie policzone automatycznie, jednak mozna.
        void setCharacterSize(unsigned int _characterSize, unsigned int _maxCharacterSize = 0);
        
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
                target.draw(this->text, states);
                //target.draw(this->hitBox, states);
            }

        //tekst
        sf::Text text;

        // hitbox tego przycisku
        sf::RectangleShape hitBox;

        // framerate jako 60 fps
        int framerate{60};

        //kiedy animacja sie skonczy to ta zmienna bedzie true
        bool animationFinished{false};
        
        //licznik animacji
        int animation{40};

        //maksymalna animacja
        int maxAnimation{40};

        //ilosc razy ile zmieni sie kolor przycisku na sekunde
        unsigned int perSecond{5};

        //kolor ktory zmieni sie po animacji
        sf::Color animationColor{sf::Color{192, 190, 190}};

        //kolor podstawowy
        sf::Color baseColor{sf::Color::White};
        
        // zawsze podczas animacji czcionka wraca do tego rozmiaru
        unsigned int defaultCharacterSize{30};

        // maksmalny rozmiar jaki osiaga czcionka podczas animacji
        unsigned int maxCharacterSize{42};

        // wyliczone w konstruktorze
        float changeSizeBy{0.2f};
    };

};