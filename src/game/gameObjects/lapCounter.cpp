/*#include "lapCounter.h"

LapCounter::LapCounter(const sf::Font& font, unsigned int characterSize)
    : currentLap(0), maxLaps(0) // 0 oznacza brak limitu
{
    lapText.setFont(font);
    lapText.setCharacterSize(characterSize);
    lapText.setFillColor(sf::Color::White);
    // Domyślna pozycja – można ją zmienić metodą setPosition()
    lapText.setPosition(10.f, 50.f);
    updateText();
}

void LapCounter::setMaxLaps(int max) {
    maxLaps = max;
    updateText();
}

void LapCounter::incrementLap() {
    // Jeżeli ustawiony jest limit i został osiągnięty, nie inkrementujemy
    if (maxLaps != 0 && currentLap >= maxLaps)
        return;
    currentLap++;
    updateText();
}

void LapCounter::reset() {
    currentLap = 0;
    updateText();
}

void LapCounter::setPosition(const sf::Vector2f& position) {
    lapText.setPosition(position);
}

int LapCounter::getCurrentLap() const {
    return currentLap;
}

int LapCounter::getMaxLaps() const {
    return maxLaps;
}

void LapCounter::updateText() {
    std::ostringstream oss;
    oss << "Lap: " << currentLap;
    if (maxLaps > 0)
        oss << " / " << maxLaps;
    lapText.setString(oss.str());
}

void LapCounter::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(lapText, states);
}*/
