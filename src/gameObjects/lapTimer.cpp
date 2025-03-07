#include "lapTimer.h"

LapTimer::LapTimer(const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
    : font(&font), frameCount(0)
{
    timerText.setFont(font);
    timerText.setCharacterSize(characterSize);
    timerText.setPosition(position);
    timerText.setFillColor(sf::Color::White);
    timerText.setString("00:00");
}

void LapTimer::update() {
    // Zakładamy, że update() jest wywoływane 60 razy na sekundę
    frameCount++;
    int totalSeconds = frameCount / 60;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    timerText.setString(oss.str());
}

void LapTimer::reset() {
    frameCount = 0;
    timerText.setString("00:00");
}

std::string LapTimer::getTime() const {
    int totalSeconds = frameCount / 60;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

void LapTimer::setPosition(const sf::Vector2f& position) {
    timerText.setPosition(position);
}

void LapTimer::setScale(const sf::Vector2f& scale) {
    timerText.setScale(scale);
}

void LapTimer::setColor(const sf::Color& color) {
    timerText.setFillColor(color);
}

void LapTimer::setCharacterSize(unsigned int size) {
    timerText.setCharacterSize(size);
}

void LapTimer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(timerText, states);
}
