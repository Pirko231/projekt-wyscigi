#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class LapTimer : public sf::Drawable {
public:
    // Konstruktor przyjmujący referencję do czcionki oraz rozmiar czcionki
    LapTimer(unsigned int characterSize = 30);

    // Aktualizuje wyświetlany czas
    void update();

    // Resetuje licznik (restart zegara)
    void reset();

    void setTexture(sf::Texture _txt) {this->backgroundTxt = _txt; this->background.setTexture(this->backgroundTxt);}

    void setFont(sf::Font _font) {this->font = _font; this->timerText.setFont(this->font);}

    // Zwraca aktualny czas w formacie MM:SS
    std::string getTime() const;

    sf::Time getElapsedTime() const;
    // Ustawia kolor tekstu (cyfr)
    void setTextColor(const sf::Color& color);

    // Ustawia rozmiar czcionki
    void setCharacterSize(unsigned int size);

    // Ustawia tło licznika – pozycję i rozmiar prostokąta
    void setPosition(const sf::Vector2f& position, const sf::Vector2f& scale = {1.f,1.f});

    // Getter dla obszaru tła (przydatny przy pozycjonowaniu)
    sf::FloatRect getBackgroundBounds() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Font font;  // Czcionka (ma własną kopię)
    sf::Text timerText;    // Tekst wyświetlający czas
    sf::Clock clock;       // Zegar mierzący upływ czasu

    // Tło licznika – czarny prostokąt
    sf::Sprite background;

    sf::Texture backgroundTxt;
};
