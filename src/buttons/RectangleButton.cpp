#include "RectangleButton.h"

btn::RectangleButton::RectangleButton(sf::Vector2f _pos, sf::Vector2f _size, sf::Color _color, sf::Color _hoverColor)
{
    rectangle.setPosition(_pos);
    rectangle.setSize(_size);
    rectangle.setFillColor(_color);

    this->baseColor = _color;
    this->hoverColor = _hoverColor;
}

void btn::RectangleButton::setPosition(sf::Vector2f _pos)
{
    rectangle.setPosition(_pos);
}

void btn::RectangleButton::setSize(sf::Vector2f _size)
{
    rectangle.setSize(_size);
}

void btn::RectangleButton::setColor(sf::Color _color)
{
    rectangle.setFillColor(_color);
    this->baseColor = _color;
}

void btn::RectangleButton::setHoverColor(sf::Color _hoverColor)
{
    this->hoverColor = _hoverColor;
}

void btn::RectangleButton::setTexture(const sf::Texture& _texture)
{
    sprite.setTexture(_texture);
    sprite.setPosition(rectangle.getPosition());
}

bool btn::RectangleButton::manageHover(sf::Vector2i mousePos, bool _clicked)
{
    if (rectangle.getGlobalBounds().contains(sf::Vector2f(mousePos)))
    {
        if (!isHovered)
        {
            rectangle.setFillColor(hoverColor);  // Zmieniamy kolor na hover
            isHovered = true;
        }

        // Jeżeli kliknięcie jest aktywne, można tu dodać kod do obsługi kliknięcia
        return true;
    }
    else
    {
        if (isHovered)
        {
            rectangle.setFillColor(baseColor);  // Przywracamy kolor początkowy
            isHovered = false;
        }
    }

    return false;  // Przyciski poza zakresem
}

sf::Vector2f btn::RectangleButton::getPosition() const
{
    return rectangle.getPosition();
}

sf::FloatRect btn::RectangleButton::getLocalBounds() const
{
    return rectangle.getLocalBounds();
}

sf::FloatRect btn::RectangleButton::getGlobalBounds() const
{
    return rectangle.getGlobalBounds();
}

void btn::RectangleButton::move(sf::Vector2f _pos)
{
    rectangle.move(_pos);
}

void btn::RectangleButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(rectangle, states);

    // Jeśli jest tekstura, rysujemy ją w środku przycisku
    if (sprite.getTexture())
    {
        target.draw(sprite, states);
    }
}
