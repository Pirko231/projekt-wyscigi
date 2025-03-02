#pragma once

#include "button.h"

class TextBox : public btn::Button
{
public:
    TextBox() = default;

    TextBox(sf::Vector2f _pos, sf::Vector2f _size);

    //uzywac w funkcji update, do funkcji handleEvents zastosowac 'manageClicks'
    bool manageHover(sf::Vector2i _mousePos, bool _clicked = false) override;

    //sprawdza czy mozna wpisywac do przycisku a potem sprawdza czy _event
    //to jakis klawisz. Kiedy jest to klawisz to przycisk na to reaguje.
    void manageClick(sf::Vector2i _mousePos, sf::Event& _event);

    void setFont(const sf::Font& _font) {this->font = _font;}

    //TODO naprawic aby rozmiar byl dobry
    void setSize(sf::Vector2f _size) {this->box.setSize(_size); this->text.setCharacterSize(_size.y);}

    //zwraca zawartosc tekstu
    sf::String getString() const {return this->textString;}
    
    sf::Vector2f getPosition() const override {return this->box.getPosition();}

    sf::FloatRect getLocalBounds() const override {return this->box.getLocalBounds();}

    sf::FloatRect getGlobalBounds() const override {return this->box.getGlobalBounds();}
        
    void setPosition(sf::Vector2f _pos) override {this->box.setPosition(_pos); this->text.setPosition(_pos);}

    void move(sf::Vector2f _offset) override {this->box.move(_offset); this->text.move(_offset);}

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        target.draw(this->box, states);
        this->text.setString(this->textString);
        target.draw(this->text, states);
    }

    //zapisuje czy teraz mozna wpisywac tekst do przycisku (jezeli true)
    //kiedy false to nie mozna wpisywac
    bool clicked{false};
    
    //kwadrat w ktorym bedzie znajdowal sie tekst. Bedzie zmienial kolor
    sf::RectangleShape box;

    sf::Font font;
    
    //tekst ktory bedzie rysowany na przycisku
    mutable sf::Text text;

    //zawartosc tekstu
    sf::String textString;
};