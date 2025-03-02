#pragma once

#include "button.h"

namespace btn
{

    class TextBox : public btn::Button
    {
    public:
        TextBox() = default;

        TextBox(sf::Vector2f _pos, sf::Vector2f _size);

        // uzywac w funkcji update, do funkcji handleEvents zastosowac 'manageClicks'
        // sprawdza czy przycisk zostal najechany oraz animuje kursor tekstu
        bool manageHover(sf::Vector2i _mousePos, bool _clicked = false) override;

        // sprawdza czy mozna wpisywac do przycisku a potem sprawdza czy _event
        // to jakis klawisz. Kiedy jest to klawisz to przycisk na to reaguje.
        void manageClick(sf::Vector2i _mousePos, sf::Event &_event);

        //ustawia czcionke na _font
        void setFont(const sf::Font &_font) { this->font = _font; }

        // TODO naprawic aby rozmiar byl dobry
        void setSize(sf::Vector2f _size, sf::Vector2f _outlineSize = {1.f,1.f})
        {
            this->box.setSize(_size);
            this->text.setCharacterSize(20);
        }

        // zwraca zawartosc tekstu
        sf::String getString() const { return this->textString; }

        sf::Vector2f getPosition() const override { return this->box.getPosition(); }

        sf::FloatRect getLocalBounds() const override { return this->box.getLocalBounds(); }

        sf::FloatRect getGlobalBounds() const override { return this->box.getGlobalBounds(); }

        void setPosition(sf::Vector2f _pos) override;

        void move(sf::Vector2f _offset) override
        {
            this->box.move(_offset);
            this->text.move(_offset);
            this->cursor.move(_offset);
        }

        //ustawia kolor obiektu na _defaultColor, kolor po najechaniu na _hoverColor,
        //kolor czcionki na _fontColor i kolor krawedzi na _outlineFillColor
        void setFillColor(sf::Color _defaultColor, sf::Color _hoverColor = sf::Color{177,177,177}, sf::Color _fontColor = sf::Color::White, sf::Color _cursorColor = sf::Color::White, sf::Color _outlineFillColor = sf::Color::Black);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override
        {
            target.draw(this->box, states);
            this->text.setString(this->textString);
            target.draw(this->cursor, states);
            target.draw(this->text, states);
        }

        // zapisuje czy teraz mozna wpisywac tekst do przycisku (jezeli true)
        // kiedy false to nie mozna wpisywac
        bool clicked{false};

        // kwadrat w ktorym bedzie znajdowal sie tekst. Bedzie zmienial kolor
        sf::RectangleShape box;

        // podstawowy kolor miejsca na tekst
        sf::Color defaultColor;

        // kolor przycisku po najechaniu
        sf::Color hoverColor;

        // kursor ktory pokazuje gdzie obecnie sie pisze
        sf::RectangleShape cursor;

        // czcionka
        sf::Font font;

        // tekst ktory bedzie rysowany na przycisku
        mutable sf::Text text;

        // zawartosc tekstu
        sf::String textString;
    };

};