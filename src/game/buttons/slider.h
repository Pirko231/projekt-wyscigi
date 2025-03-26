#pragma once
#include <SFML/Graphics.hpp>
#include "button.h"
#include <string>

namespace btn {

    // Klasa Slider dziedziczy po btn::Button
    // Suwak składa się z linii (sf::RectangleShape), kropki (sf::CircleShape)
    // oraz licznika (sf::Text), który wyświetla aktualną wartość.
    class Slider : public Button
    {
    public:
        // Konstruktor - ustawia początkowe wartości suwaka
        // pos         - pozycja linii suwaka
        // size        - rozmiar linii suwaka
        // lineColor   - kolor linii suwaka
        // dotColor    - kolor kropki (uchwytu)
        // linkedValue - wskaźnik do zmiennej int, której wartość będzie aktualizowana
        Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color lineColor, sf::Color dotColor, int* linkedValue);

        // Konstruktor przyjmujący tylko wskaźnik (domyślne parametry)
        Slider(int* linkedValue)
            : Slider(sf::Vector2f(0.f, 0.f), sf::Vector2f(400.f, 5.f), sf::Color::Black, sf::Color::Red, linkedValue)
        { }

        // Nadpisane funkcje z klasy Button
        void setPosition(sf::Vector2f pos) override;
        sf::Vector2f getPosition() const override;
        sf::FloatRect getLocalBounds() const override;
        sf::FloatRect getGlobalBounds() const override;
        void move(sf::Vector2f offset) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool manageHover(sf::Vector2i mousePos, bool clicked = false) override;

        // Funkcje do zmiany ustawień suwaka
        void setSize(sf::Vector2f size);
        void setLineColor(sf::Color color);
        void setDotColor(sf::Color color);
        void setDotHoverColor(sf::Color color);

        // Aktualizuje wartość suwaka (i licznik) na podstawie pozycji kropki
        void updateValue();

        // Nowe funkcje do obsługi licznika
        // Ustawia czcionkę licznika – przekazywana przez argument (bez wczytywania z pliku)
        void setCounterFont(const sf::Font &font);
        // Ustawia przesunięcie licznika względem pozycji kropki
        void setCounterOffset(const sf::Vector2f &offset);

    private:
        sf::RectangleShape line;  // Linia suwaka
        sf::CircleShape dot;      // Kropka – uchwyt przesuwania

        sf::Color baseDotColor;   // Podstawowy kolor kropki
        sf::Color hoverDotColor;  // Kolor kropki przy najechaniu

        int* linkedValue;         // Wskaźnik do zmiennej, którą suwak będzie aktualizować
        int minValue, maxValue;   // Zakres wartości (domyślnie 0–100)

        bool isDragging;          // Flaga sprawdzająca, czy kropka jest przeciągana

        // Nowe pola do obsługi licznika (counter)
        sf::Text counterText;     // Tekst wyświetlający wartość
        sf::Vector2f counterOffset; // Przesunięcie pozycji licznika względem kropki
    };

} // namespace btn
