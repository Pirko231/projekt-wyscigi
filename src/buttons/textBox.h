#pragma once

#include <SFML/Graphics.hpp>
#include "button.h" // plik z deklaracją klasy btn::Button

namespace btn {

class TextBox : public Button {
public:
    TextBox();
    virtual ~TextBox();

    // Implementacja funkcji wirtualnych z klasy Button:
    virtual bool manageHover(sf::Vector2i _mousePos, bool _clicked = false) override;
    virtual sf::Vector2f getPosition() const override;
    virtual sf::FloatRect getLocalBounds() const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual void setPosition(sf::Vector2f _pos) override;
    virtual void move(sf::Vector2f _pos) override;

    // Ustawianie czcionki (przekazywana jako argument)
    void setFont(const sf::Font& _font);
    // Ustawienie rozmiaru czcionki – opcjonalnie (defaultowo ustawiony rozmiar obliczany jest przez klasę)
    void setCharacterSize(unsigned int size);
    // Ustawienia kolorów:
    void setTextColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineSize(float size);
    // Ustawienie koloru animacji (dla stanów hover/aktywny)
    void setAnimationColor(const sf::Color& color);
    // Ustawienie koloru kursora
    void setCursorColor(const sf::Color& color);
    // Ustawienie rozmiaru TextBoxa (jego tła)
    void setSize(sf::Vector2f size);
    // Ustawienie limitu znaków wprowadzanych przez użytkownika
    void setLimit(unsigned int limit);

    // Pobranie przechwyconego tekstu
    std::string getText() const;

    // Funkcje obsługi zdarzeń – należy wywoływać przy obsłudze pętli zdarzeń SFML
    // Zwraca true, gdy naciśnięto Enter (można pobrać tekst), false w przeciwnym wypadku.
    bool handleEvent(const sf::Event& event);
    // Aktualizacja stanu (np. migania kursora) – wywoływana w głównej pętli aplikacji
    void update();

    // Reset zawartości TextBox – usuwa cały wpisany tekst
    void reset();

    // Utrata fokusu – gdy kliknięto poza TextBoxem
    void loseFocus();

private:
    // Funkcja rysowania (wywoływana automatycznie przy target.draw)
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::RectangleShape background;   // Tło przycisku (TextBoxa)
    sf::Text displayedText;          // Wyświetlany tekst
    const sf::Font* font;            // Wskaźnik na czcionkę (ustawiany przez setFont)
    sf::RectangleShape cursor;       // Migający kursor

    bool focused;                    // Czy TextBox posiada fokus
    unsigned int charLimit;          // Maksymalna liczba znaków do wprowadzenia
    sf::Clock blinkClock;            // Zegar do obsługi migania kursora
    bool showCursor;                 // Flaga określająca, czy kursor ma być widoczny

    // Domyślne kolory dla poszczególnych stanów:
    sf::Color normalColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Color textColor;
    sf::Color cursorColor;
    float outlineSize;
};

} // namespace btn
