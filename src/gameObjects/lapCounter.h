/*#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

// Klasa LapCounter – odpowiada za liczenie okrążeń oraz wyświetlanie bieżącej wartości.
// Pozwala ustawić maksymalną liczbę okrążeń, zwiększać licznik, resetować oraz ustawiać pozycję wyświetlanego tekstu.
class LapCounter : public sf::Drawable {
public:
    // Konstruktor przyjmujący referencję do czcionki oraz opcjonalny rozmiar czcionki
    LapCounter(const sf::Font& font, unsigned int characterSize = 30);

    // Ustawia maksymalną liczbę okrążeń (0 oznacza brak limitu)
    void setMaxLaps(int max);

    // Zwiększa licznik okrążeń (jeśli nie przekroczono limitu)
    void incrementLap();

    // Resetuje licznik okrążeń
    void reset();

    // Ustawia pozycję wyświetlanego tekstu
    void setPosition(const sf::Vector2f& position);

    // Zwraca bieżącą liczbę okrążeń
    int getCurrentLap() const;

    // Zwraca ustawiony limit okrążeń
    int getMaxLaps() const;

private:
    int currentLap;    // Aktualna liczba okrążeń
    int maxLaps;       // Maksymalna liczba okrążeń (0 oznacza brak limitu)
    sf::Text lapText;  // Tekst wyświetlający licznik okrążeń

    // Aktualizuje zawartość tekstu na podstawie bieżących danych
    void updateText();

    // Metoda rysująca – wywoływana automatycznie przez SFML
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};*/
