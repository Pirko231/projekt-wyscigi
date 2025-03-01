#include "slider.h"
#include <cmath>

// Statyczna zmienna globalna – aktywny slider (tylko jeden na raz)
namespace {
    btn::Slider* activeSlider = nullptr;
}

namespace btn {

    // Konstruktor - ustawia wartości początkowe
    Slider::Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color lineColor, sf::Color dotColor, int* linkedValue)
        : linkedValue(linkedValue), minValue(0), maxValue(100), isDragging(false)
    {
        // Ustawienie linii suwaka
        line.setPosition(pos);
        line.setSize(size);
        line.setFillColor(lineColor);

        // Ustawienie kropki – promień kropki to 1.5-krotność wysokości linii
        float dotRadius = size.y * 1.5f;
        dot.setRadius(dotRadius);
        dot.setFillColor(dotColor);
        baseDotColor = dotColor;
        hoverDotColor = sf::Color::White;

        // Wyśrodkowanie kropki – ustawiamy origin na środek kropki
        dot.setOrigin(dotRadius, dotRadius);

        // Ustawiamy kropkę na odpowiedniej pozycji w zależności od wartości linkedValue
        float percent = 0.f;
        if (linkedValue)
            percent = static_cast<float>(*linkedValue - minValue) / (maxValue - minValue);
        if (percent < 0.f) percent = 0.f;
        if (percent > 1.f) percent = 1.f;
        dot.setPosition(pos.x + percent * size.x, pos.y + size.y / 2);
    }

    void Slider::setPosition(sf::Vector2f pos)
    {
        line.setPosition(pos);
        float percent = 0.f;
        if (linkedValue)
            percent = static_cast<float>(*linkedValue - minValue) / (maxValue - minValue);
        if (percent < 0.f) percent = 0.f;
        if (percent > 1.f) percent = 1.f;
        dot.setPosition(pos.x + percent * line.getSize().x, pos.y + line.getSize().y / 2);
    }

    sf::Vector2f Slider::getPosition() const
    {
        return line.getPosition();
    }

    sf::FloatRect Slider::getLocalBounds() const
    {
        return line.getLocalBounds();
    }

    sf::FloatRect Slider::getGlobalBounds() const
    {
        return line.getGlobalBounds();
    }

    void Slider::move(sf::Vector2f offset)
    {
        line.move(offset);
        dot.move(offset);
    }

    void Slider::setSize(sf::Vector2f size)
    {
        line.setSize(size);
        float dotRadius = size.y * 1.5f;
        dot.setRadius(dotRadius);
        dot.setOrigin(dotRadius, dotRadius);
        float percent = 0.f;
        if (linkedValue)
            percent = static_cast<float>(*linkedValue - minValue) / (maxValue - minValue);
        if (percent < 0.f) percent = 0.f;
        if (percent > 1.f) percent = 1.f;
        dot.setPosition(line.getPosition().x + percent * size.x, line.getPosition().y + size.y / 2);
    }

    void Slider::setLineColor(sf::Color color)
    {
        line.setFillColor(color);
    }

    void Slider::setDotColor(sf::Color color)
    {
        dot.setFillColor(color);
        baseDotColor = color;
    }

    void Slider::setDotHoverColor(sf::Color color)
    {
        hoverDotColor = color;
    }

    // Zarządza interakcją myszy
    bool Slider::manageHover(sf::Vector2i mousePos, bool clicked)
    {
        sf::Vector2f mouseWorldPos = static_cast<sf::Vector2f>(mousePos);
        float centerY = line.getPosition().y + line.getSize().y / 2;
        float verticalTolerance = 20.f; // Tolerancja pionowa

        if (clicked) {
            // Jeśli nikt nie jest aktywny, sprawdzamy, czy kliknięto na ten slider
            if (activeSlider == nullptr) {
                if (std::abs(mouseWorldPos.y - centerY) < verticalTolerance &&
                    dot.getGlobalBounds().contains(mouseWorldPos))
                {
                    activeSlider = this;
                    isDragging = true;
                }
            }
            // Jeśli ten slider jest aktywny, wykonujemy przeciąganie
            if (activeSlider == this && isDragging) {
                float newX = mouseWorldPos.x;
                float minX = line.getPosition().x;
                float maxX = line.getPosition().x + line.getSize().x;
                if (newX < minX)
                    newX = minX;
                if (newX > maxX)
                    newX = maxX;
                dot.setPosition(newX, centerY);
                updateValue();
            }
            return (activeSlider == this);
        }
        else {
            // Zwolnij aktywny slider, jeśli to ten obiekt
            if (activeSlider == this) {
                activeSlider = nullptr;
                isDragging = false;
            }
        }

        // Jeśli myszka jest blisko środka linii, zmieniamy kolor kropki
        if (std::abs(mouseWorldPos.y - centerY) < verticalTolerance &&
            dot.getGlobalBounds().contains(mouseWorldPos))
            dot.setFillColor(hoverDotColor);
        else
            dot.setFillColor(baseDotColor);

        return false;
    }

    void Slider::updateValue()
    {
        float relativePos = dot.getPosition().x - line.getPosition().x;
        float lineWidth = line.getSize().x;
        float percent = relativePos / lineWidth;
        if (percent < 0.f) percent = 0.f;
        if (percent > 1.f) percent = 1.f;
        int value = minValue + static_cast<int>(percent * (maxValue - minValue));
        if (linkedValue)
            *linkedValue = value;
    }

    void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(line, states);
        target.draw(dot, states);
    }

} // namespace btn
