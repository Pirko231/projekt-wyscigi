#include "lapTimer.h"

LapTimer::LapTimer(const sf::Font& font, unsigned int characterSize)
    : font(&font)
{
    timerText.setFont(font);
    timerText.setCharacterSize(characterSize);
    timerText.setFillColor(sf::Color::Red);  // Czerwony kolor cyfr
    timerText.setString("00:00");

    // Ustawienie domyślnego tła – lewy górny róg (353,124), rozmiar 244x138, kolor czarny
    backgroundRect.setPosition(sf::Vector2f(353.f, 124.f));
    backgroundRect.setSize(sf::Vector2f(244.f, 138.f));
    backgroundRect.setFillColor(sf::Color::Black);
}

void LapTimer::update() {
    sf::Time elapsed = clock.getElapsedTime();
    int totalSeconds = static_cast<int>(elapsed.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    timerText.setString(oss.str());
}

void LapTimer::reset() {
    clock.restart();
    timerText.setString("00:00");
}

std::string LapTimer::getTime() const {
    sf::Time elapsed = clock.getElapsedTime();
    int totalSeconds = static_cast<int>(elapsed.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

void LapTimer::setTextColor(const sf::Color& color) {
    timerText.setFillColor(color);
}

void LapTimer::setCharacterSize(unsigned int size) {
    timerText.setCharacterSize(size);
}

void LapTimer::setBackground(const sf::Vector2f& position, const sf::Vector2f& size) {
    backgroundRect.setPosition(position);
    backgroundRect.setSize(size);
}

sf::FloatRect LapTimer::getBackgroundBounds() const {
    return backgroundRect.getGlobalBounds();
}

void LapTimer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Najpierw rysujemy tło
    target.draw(backgroundRect, states);

    // Aby wyśrodkować tekst w obrębie tła, obliczamy środek backgroundRect
    sf::Vector2f rectCenter = backgroundRect.getPosition() + backgroundRect.getSize() / 2.f;
    sf::FloatRect textBounds = timerText.getLocalBounds();
    // Ustawiamy origin tekstu na środek (konwersja przez const_cast – bezpieczna przy rysowaniu)
    const_cast<sf::Text&>(timerText).setOrigin(textBounds.left + textBounds.width / 2.f,
                                                textBounds.top + textBounds.height / 2.f);
    const_cast<sf::Text&>(timerText).setPosition(rectCenter);

    target.draw(timerText, states);
}
