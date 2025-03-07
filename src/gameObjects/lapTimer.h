#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class LapTimer : public sf::Drawable {
public:
    // Konstruktor przyjmujący referencję do czcionki, rozmiar czcionki i pozycję
    LapTimer(const sf::Font& font, unsigned int characterSize = 30, const sf::Vector2f& position = {0.f, 0.f});

    // Funkcja update – wywoływana 60 razy na sekundę (przy framerate 60)
    void update();

    // Resetuje licznik do zera
    void reset();

    // Zwraca aktualny czas w formacie MM:SS
    std::string getTime() const;

    // Ustawienia wyglądu
    void setPosition(const sf::Vector2f& position);
    void setScale(const sf::Vector2f& scale);
    void setColor(const sf::Color& color);
    void setCharacterSize(unsigned int size);

private:
    // Metoda rysująca obiekt – wywoływana przez SFML
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const sf::Font* font;  // Czcionka (obiekt nie jest własnością klasy)
    sf::Text timerText;    // Tekst wyświetlający czas
    int frameCount;        // Liczba klatek (do przeliczania czasu)
};
