#include "lapTimer.h"

LapTimer::LapTimer(unsigned int characterSize)
{
    //timerText.setFont(font);
    timerText.setCharacterSize(characterSize);
    timerText.setFillColor(sf::Color::Red);  // Czerwony kolor cyfr
    timerText.setString("00:00");

    this->lapText.setCharacterSize(characterSize - 2U);
    this->lapText.setFillColor(sf::Color::Red);

    //backgroundTxt = txt;

    // Ustawienie domyślnego tła – lewy górny róg (353,124), rozmiar 244x138, kolor czarny
    //background.setPosition(sf::Vector2f(353.f, 124.f));
    //background.setTexture(backgroundTxt);
    //background.setScale(0.3f,0.3f);
    //background.setFillColor(sf::Color::Black);
}

void LapTimer::update() {
    sf::Time elapsed = clock.getElapsedTime();
    int totalSeconds = static_cast<int>(elapsed.asSeconds());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    this->lapText.setString(std::to_string(this->currentLap) + "/" + std::to_string(this->maxLap));
    
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":"
        << std::setw(2) << std::setfill('0') << seconds;
    timerText.setString(oss.str());
}

void LapTimer::reset() {
    clock.restart();
    timerText.setString("00:00");
}

sf::Time LapTimer::getElapsedTime() const {
    return clock.getElapsedTime();
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

void LapTimer::setPosition(const sf::Vector2f& position, const sf::Vector2f& scale) {
    background.setPosition(position);
    background.setScale(scale);
    timerText.setPosition(position.x + 80.f, position.y);
}

sf::FloatRect LapTimer::getBackgroundBounds() const {
    return background.getGlobalBounds();
}

void LapTimer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Najpierw rysujemy tło
    target.draw(background, states);

    // Aby wyśrodkować tekst w obrębie tła, obliczamy środek backgroundRect
    sf::Vector2f rectCenter {background.getPosition().x + background.getGlobalBounds().width / 1.45f, background.getPosition().y + background.getGlobalBounds().height / 2.f};
    sf::FloatRect textBounds = timerText.getLocalBounds();
    // Ustawiamy origin tekstu na środek (konwersja przez const_cast – bezpieczna przy rysowaniu)
    const_cast<sf::Text&>(timerText).setOrigin(textBounds.left + textBounds.width / 2.f,
                                                textBounds.top + textBounds.height / 2.f);
    const_cast<sf::Text&>(timerText).setPosition(rectCenter);

    const_cast<sf::Text&>(this->lapText).setOrigin(textBounds.left + textBounds.width * 1.8f, textBounds.top + textBounds.height / 2.f);
    const_cast<sf::Text&>(this->lapText).setPosition(rectCenter);

    target.draw(timerText, states);
    target.draw(this->lapText, states);
}
