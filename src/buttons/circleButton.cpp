#include "CircleButton.h"
#include <cmath>

namespace btn
{
    CircleButton::CircleButton(sf::Vector2f _pos, float _radius, sf::Color _baseColor)
    {
        circle.setPosition(_pos);
        circle.setRadius(_radius);
        baseColor = _baseColor;
        circle.setFillColor(baseColor);
        // Ustawiamy origin na środek, aby skalowanie odbywało się symetrycznie
        circle.setOrigin(_radius, _radius);
    }

    void CircleButton::setPosition(sf::Vector2f _pos)
    {
        circle.setPosition(_pos);
    }

    void CircleButton::setRadius(float _radius)
    {
        circle.setRadius(_radius);
        circle.setOrigin(_radius, _radius);
    }

    void CircleButton::setColor(sf::Color _color)
    {
        baseColor = _color;
        circle.setFillColor(baseColor);
    }

    void CircleButton::setHoverScaleFactor(float factor)
    {
        hoverScaleFactor = factor;
    }

    bool CircleButton::manageHover(sf::Vector2i _mousePos, bool /*_clicked*/)
    {
        sf::Vector2f mousePosF(static_cast<float>(_mousePos.x), static_cast<float>(_mousePos.y));
        sf::Vector2f center = circle.getPosition();
        float radius = circle.getRadius();
        
        // Obliczamy dystans między kursorem a środkiem koła
        float dx = mousePosF.x - center.x;
        float dy = mousePosF.y - center.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= radius)
        {
            if (!isHovered)
            {
                // Zmiana skali, ale nie zmieniamy koloru
                circle.setScale(hoverScaleFactor, hoverScaleFactor);
                isHovered = true;
            }
            return true;
        }
        else
        {
            if (isHovered)
            {
                // Powrót do domyślnej skali, kolor pozostaje niezmieniony
                circle.setScale(1.f, 1.f);
                isHovered = false;
            }
            return false;
        }
    }

    sf::Vector2f CircleButton::getPosition() const
    {
        return circle.getPosition();
    }

    sf::FloatRect CircleButton::getLocalBounds() const
    {
        return circle.getLocalBounds();
    }

    sf::FloatRect CircleButton::getGlobalBounds() const
    {
        return circle.getGlobalBounds();
    }

    void CircleButton::move(sf::Vector2f _offset)
    {
        circle.move(_offset);
    }

    void CircleButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(circle, states);
    }
}
