#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"  

namespace btn
{
    class CircleButton : public Button
    {
    public:
        // Konstruktor domyślny
        CircleButton() = default;

        // Konstruktor z pozycją, promieniem oraz kolorami.
        // Domyślnie kolor przycisku to biały.
        CircleButton(sf::Vector2f _pos, float _radius, sf::Color _baseColor = sf::Color::White);

        // Ustawia pozycję przycisku (środek koła)
        void setPosition(sf::Vector2f _pos) override;

        // Ustawia promień koła
        void setRadius(float _radius);

        // Ustawia kolor podstawowy przycisku
        void setColor(sf::Color _color);

        // Ustawia współczynnik powiększenia przy najechaniu (domyślnie 1.1f)
        void setHoverScaleFactor(float factor);

        // Obsługuje stan najechania – przy powiększaniu nie zmienia koloru
        bool manageHover(sf::Vector2i _mousePos, bool _clicked = false) override;

        // Zwraca pozycję przycisku (środek koła)
        sf::Vector2f getPosition() const override;

        // Zwraca lokalne granice kształtu
        sf::FloatRect getLocalBounds() const override;

        // Zwraca globalne granice kształtu
        sf::FloatRect getGlobalBounds() const override;

        // Przesuwa kształt przycisku
        void move(sf::Vector2f _offset) override;

        // Destruktor
        ~CircleButton() override = default;

    private:
        // Funkcja rysująca przycisk (wywoływana przez sf::Drawable)
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::CircleShape circle;    // Główny kształt przycisku (koło)
        sf::Color baseColor;       // Kolor przycisku (niezmieniany podczas animacji)
        float hoverScaleFactor {1.1f}; // Współczynnik powiększenia przy najechaniu
        bool isHovered {false};    // Flaga określająca, czy przycisk jest aktualnie najechany
    };
}
