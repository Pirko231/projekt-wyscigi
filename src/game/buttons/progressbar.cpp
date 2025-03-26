#include "progressbar.h"
#include <algorithm> // std::clamp

namespace btn {

ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size, int* linkedValue, sf::Color outlineColor)
    : linkedValue(linkedValue), minValue(0), maxValue(100)
{
    backgroundBar.setPosition(pos);
    backgroundBar.setSize(size);
    backgroundBar.setFillColor(sf::Color::Transparent);
    backgroundBar.setOutlineColor(outlineColor);
    backgroundBar.setOutlineThickness(1.f);

    fillBar.setPosition(pos);
    fillBar.setSize({0.f, size.y}); // startowo 0 szerokości
    fillBar.setFillColor(sf::Color::Red);

    updateBar();
}

void ProgressBar::setPosition(sf::Vector2f pos)
{
    backgroundBar.setPosition(pos);
    fillBar.setPosition(pos);
    updateBar();
}

sf::Vector2f ProgressBar::getPosition() const
{
    return backgroundBar.getPosition();
}

sf::FloatRect ProgressBar::getLocalBounds() const
{
    return backgroundBar.getLocalBounds();
}

sf::FloatRect ProgressBar::getGlobalBounds() const
{
    return backgroundBar.getGlobalBounds();
}

void ProgressBar::move(sf::Vector2f offset)
{
    backgroundBar.move(offset);
    fillBar.move(offset);
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(backgroundBar, states);
    target.draw(fillBar, states);
}

bool ProgressBar::manageHover(sf::Vector2i /*mousePos*/, bool /*clicked*/)
{
    // ProgressBar nie reaguje na interakcje, zwracamy false
    return false;
}

void ProgressBar::setSize(sf::Vector2f size)
{
    backgroundBar.setSize(size);
    updateBar();
}

void ProgressBar::setValue(int value)
{
    if (linkedValue)
    {
        // Ograniczamy do zakresu [minValue, maxValue]
        *linkedValue = std::clamp(value, minValue, maxValue);
        updateBar();
    }
}

int ProgressBar::getValue() const
{
    return (linkedValue) ? *linkedValue : 0;
}

void ProgressBar::setOutlineColor(sf::Color color)
{
    backgroundBar.setOutlineColor(color);
}

void ProgressBar::updateBar()
{
    if (!linkedValue) return;
    float range = static_cast<float>(maxValue - minValue);
    float pct   = (*linkedValue - minValue) / range; 
    pct         = std::max(0.f, std::min(1.f, pct)); 

    // Ustaw szerokość wypełnienia
    sf::Vector2f size = backgroundBar.getSize();
    fillBar.setSize({ size.x * pct, size.y });

    updateBarColor();
}

void ProgressBar::updateBarColor()
{
    if (!linkedValue) return;
    float pct = 100.f * (*linkedValue - minValue) / (maxValue - minValue);

    if (pct < 30.f)
        fillBar.setFillColor(sf::Color::Red);
    else if (pct < 60.f)
        fillBar.setFillColor(sf::Color::Yellow);
    else if (pct < 90.f)
        fillBar.setFillColor(sf::Color::Green);
    else
        fillBar.setFillColor(sf::Color::Blue);
}

} // namespace btn
