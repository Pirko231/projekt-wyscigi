#include "slider.h"
#include <cmath>
#include <string>

namespace {
    // Statyczna zmienna globalna – aktywny slider (tylko jeden na raz)
    btn::Slider* activeSlider = nullptr;
}

namespace btn {

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
        dot.setOrigin(dotRadius, dotRadius);

        // Ustawienie kropki na odpowiedniej pozycji w zależności od wartości linkedValue
        float percent = 0.f;
        if (linkedValue)
            percent = static_cast<float>(*linkedValue - minValue) / (maxValue - minValue);
        if (percent < 0.f) percent = 0.f;
        if (percent > 1.f) percent = 1.f;
        dot.setPosition(pos.x + percent * size.x, pos.y + size.y / 2);

        // Inicjalizacja licznika – wyświetla aktualną wartość
        counterText.setString(linkedValue ? std::to_string(*linkedValue) : "0");
        counterText.setFillColor(sf::Color::White);
        counterText.setCharacterSize(16);
        // Ustawienie domyślnego przesunięcia licznika względem linii suwaka (np. 10 pikseli na prawo, lekko wyśrodkowany pionowo)
        counterOffset = sf::Vector2f(10.f, -size.y / 2);
        counterText.setPosition(line.getPosition().x + size.x + counterOffset.x, line.getPosition().y + size.y / 2 + counterOffset.y);
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
        // Pozycja licznika względem linii
        counterText.setPosition(pos.x + line.getSize().x + counterOffset.x, pos.y + line.getSize().y / 2 + counterOffset.y);
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
        counterText.move(offset);
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
        // Aktualizacja pozycji licznika względem zmienionego rozmiaru linii
        counterText.setPosition(line.getPosition().x + size.x + counterOffset.x, line.getPosition().y + size.y / 2 + counterOffset.y);
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

    bool Slider::manageHover(sf::Vector2i mousePos, bool clicked)
    {
        sf::Vector2f mouseWorldPos = static_cast<sf::Vector2f>(mousePos);
        float centerY = line.getPosition().y + line.getSize().y / 2;
        float verticalTolerance = 20.f; // Tolerancja pionowa

        if (clicked) {
            if (activeSlider == nullptr) {
                if (std::abs(mouseWorldPos.y - centerY) < verticalTolerance &&
                    dot.getGlobalBounds().contains(mouseWorldPos))
                {
                    activeSlider = this;
                    isDragging = true;
                }
            }
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
            if (activeSlider == this) {
                activeSlider = nullptr;
                isDragging = false;
            }
        }

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

        counterText.setString(std::to_string(value));
        // Licznik ustawiany względem linii, nie kropki
        counterText.setPosition(line.getPosition().x + line.getSize().x + counterOffset.x, line.getPosition().y + line.getSize().y / 2 + counterOffset.y);
    }

    void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(line, states);
        target.draw(dot, states);
        target.draw(counterText, states);
    }

    void Slider::setCounterFont(const sf::Font &font)
    {
        counterText.setFont(font);
    }

    void Slider::setCounterOffset(const sf::Vector2f &offset)
    {
        counterOffset = offset;
        counterText.setPosition(line.getPosition().x + line.getSize().x + counterOffset.x, line.getPosition().y + line.getSize().y / 2 + counterOffset.y);
    }

} // namespace btn
