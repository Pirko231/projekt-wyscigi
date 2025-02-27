#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

namespace btn
{
    class RectangleButton : public Button
    {
    public:
        // Konstruktor domyślny
        RectangleButton() = default;

        // Konstruktor z pozycją, rozmiarem i kolorami
        RectangleButton(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _color, sf::Color _hoverColor);

        // Ustawia pozycję przycisku
        void setPosition(sf::Vector2f _pos) override;

        // Ustawia rozmiar przycisku
        void setSize(sf::Vector2f _size);

        // Ustawia kolor przycisku
        void setColor(sf::Color _color);

        // Ustawia kolor animacji (kolor, na który przycisk zmienia się po najechaniu)
        void setHoverColor(sf::Color _hoverColor);

        // Ustawia teksturę w środku przycisku
        void setTexture(const sf::Texture& _texture);

        // Sprawdza, czy myszka jest na przycisku
        bool manageHover(sf::Vector2i mousePos, bool _clicked = false) override;

        // Zwraca pozycję przycisku
        sf::Vector2f getPosition() const override;

        // Zwraca lokalne granice przycisku
        sf::FloatRect getLocalBounds() const override;

        // Zwraca globalne granice przycisku
        sf::FloatRect getGlobalBounds() const override;

        // Przesuwa przycisk
        void move(sf::Vector2f _pos) override;

        // Destruktor
        ~RectangleButton() override = default;

    private:
        // Rysowanie przycisku
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        // Przycisk jako prostokąt
        sf::RectangleShape rectangle;

        // Obrazek, który będzie w środku przycisku
        sf::Sprite sprite;

        // Kolor podstawowy i kolor animacji
        sf::Color baseColor;
        sf::Color hoverColor;

        // Przechowuje stan, czy przycisk jest najechany
        bool isHovered{false};
    };
}
