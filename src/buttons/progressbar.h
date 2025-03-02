#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"

namespace btn {

    class ProgressBar : public Button
    {
    public:
        // Konstruktor (pozycja, rozmiar, wskaźnik na wartość, opcjonalny kolor obrysu)
        ProgressBar(sf::Vector2f pos, sf::Vector2f size, int* linkedValue, sf::Color outlineColor = sf::Color::Black);

        // Wymagane funkcje wirtualne z Button
        void setPosition(sf::Vector2f pos) override;
        sf::Vector2f getPosition() const override;
        sf::FloatRect getLocalBounds() const override;
        sf::FloatRect getGlobalBounds() const override;
        void move(sf::Vector2f offset) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool manageHover(sf::Vector2i mousePos, bool clicked = false) override;

        // Dodatkowe metody
        void setSize(sf::Vector2f size);
        void setValue(int value);
        int  getValue() const;
        void setOutlineColor(sf::Color color);

    private:
        void updateBar();       // Aktualizuje szerokość i kolor paska
        void updateBarColor();  // Zmienia kolor w zależności od procentu

        sf::RectangleShape backgroundBar; 
        sf::RectangleShape fillBar;

        int* linkedValue; // Wartość (0-100) przechowywana w zewnętrznej zmiennej
        int  minValue;    // Domyślnie 0
        int  maxValue;    // Domyślnie 100
    };

} // namespace btn
