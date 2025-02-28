#pragma once
#include <SFML/Graphics.hpp>  // Wymagane dla obiektów graficznych SFML
#include "button.h"  // Zakładam, że klasa Button jest zdefiniowana w pliku button.h

namespace btn {

    // Klasa Slider dziedziczy po klasie Button
    // Dzięki temu, możemy używać funkcji z klasy Button, jak np. draw().
    class Slider : public Button
    {
    public:
        // Konstruktor - ustawia początkowe wartości suwaka
        Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color lineColor, sf::Color dotColor, int* linkedValue);

        // Nadpisane funkcje z klasy Button
        void setPosition(sf::Vector2f pos) override;  // Ustawienie pozycji suwaka (linii i kropki)
        sf::Vector2f getPosition() const override;  // Pobranie pozycji suwaka
        sf::FloatRect getLocalBounds() const override;  // Pobranie lokalnych granic suwaka
        sf::FloatRect getGlobalBounds() const override;  // Pobranie globalnych granic suwaka
        void move(sf::Vector2f offset) override;  // Przemieszczanie suwaka o dany wektor
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;  // Rysowanie suwaka na ekranie
        bool manageHover(sf::Vector2i mousePos, bool clicked = false) override;  // Zarządzanie interakcją z myszką (np. zmiana koloru)

        // Funkcje do zmiany ustawień suwaka
        void setSize(sf::Vector2f size);  // Ustawienie rozmiaru suwaka (linii)
        void setLineColor(sf::Color color);  // Ustawienie koloru linii
        void setDotColor(sf::Color color);  // Ustawienie koloru kropki
        void setDotHoverColor(sf::Color color);  // Ustawienie koloru kropki po najechaniu myszką

        // Funkcja aktualizująca wartość suwaka na podstawie jego pozycji
        void updateValue();

    private:
        sf::RectangleShape line;  // Linia, po której przesuwa się kropka
        sf::CircleShape dot;  // Kropka, która jest przesuwana po linii

        sf::Color baseDotColor;  // Podstawowy kolor kropki
        sf::Color hoverDotColor;  // Kolor kropki, gdy kursor znajduje się nad nią

        int* linkedValue;  // Wskaźnik do zmiennej, którą suwak będzie aktualizować
        int minValue, maxValue;  // Zakres wartości suwaka (od minValue do maxValue)

        bool isDragging;  // Flaga sprawdzająca, czy kropka jest przeciągana przez użytkownika
    };

} // namespace btn
