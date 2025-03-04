#include "textBox.h"

namespace btn {

TextBox::TextBox() 
    : font(nullptr),
      focused(false),
      charLimit(20),
      showCursor(true),
      outlineSize(2.f)
{
    // Konfiguracja tła TextBoxa
    background.setSize(sf::Vector2f(200.f, 50.f));
    background.setFillColor(sf::Color(200, 200, 200));
    background.setOutlineThickness(outlineSize);
    background.setOutlineColor(sf::Color::Black);

    // Konfiguracja tekstu – domyślne ustawienia
    displayedText.setFillColor(sf::Color::Black);
    displayedText.setCharacterSize(20);
    // Tekst rysowany z lekkim marginesem od krawędzi tła:
    displayedText.setPosition(background.getPosition().x + 5, background.getPosition().y + 5);

    // Konfiguracja kursora – prostokąt reprezentujący kursor
    cursor.setFillColor(sf::Color::Black);
    cursor.setSize(sf::Vector2f(2.f, displayedText.getCharacterSize()));
    cursor.setPosition(displayedText.getPosition().x + displayedText.getLocalBounds().width + 2,
                         displayedText.getPosition().y);

    // Ustawienia domyślnych kolorów
    normalColor = background.getFillColor();
    hoverColor = sf::Color(180, 180, 180);
    activeColor = sf::Color(160, 160, 160);
    textColor = displayedText.getFillColor();
    cursorColor = cursor.getFillColor();
}

TextBox::~TextBox() {
    // Brak dynamicznie alokowanych zasobów
}

bool TextBox::manageHover(sf::Vector2i _mousePos, bool _clicked) {
    sf::Vector2f mousePos(static_cast<float>(_mousePos.x), static_cast<float>(_mousePos.y));
    if (background.getGlobalBounds().contains(mousePos)) {
        if (_clicked) {
            focused = true;
            background.setFillColor(activeColor);
            blinkClock.restart();
            showCursor = true;
        } else if (!focused) {
            background.setFillColor(hoverColor);
        }
        return true;
    } else {
        if (_clicked) {
            loseFocus();
        }
        if (!focused)
            background.setFillColor(normalColor);
        return false;
    }
}

sf::Vector2f TextBox::getPosition() const {
    return background.getPosition();
}

sf::FloatRect TextBox::getLocalBounds() const {
    return background.getLocalBounds();
}

sf::FloatRect TextBox::getGlobalBounds() const {
    return background.getGlobalBounds();
}

void TextBox::setPosition(sf::Vector2f _pos) {
    background.setPosition(_pos);
    displayedText.setPosition(_pos.x + 5, _pos.y + 5);
    cursor.setPosition(displayedText.getPosition().x + displayedText.getLocalBounds().width + 2,
                         displayedText.getPosition().y);
}

void TextBox::move(sf::Vector2f _pos) {
    background.move(_pos);
    displayedText.move(_pos);
    cursor.move(_pos);
}

void TextBox::setFont(const sf::Font& _font) {
    font = &_font;
    displayedText.setFont(_font);
}

void TextBox::setCharacterSize(unsigned int size) {
    displayedText.setCharacterSize(size);
    // Aktualizacja wysokości kursora
    cursor.setSize(sf::Vector2f(cursor.getSize().x, size));
}

void TextBox::setTextColor(const sf::Color& color) {
    textColor = color;
    displayedText.setFillColor(color);
}

void TextBox::setOutlineColor(const sf::Color& color) {
    background.setOutlineColor(color);
}

void TextBox::setOutlineSize(float size) {
    outlineSize = size;
    background.setOutlineThickness(size);
}

void TextBox::setAnimationColor(const sf::Color& color) {
    // Ustawia kolor dla stanów hover/aktywny
    hoverColor = color;
    activeColor = color;
    if (focused)
        background.setFillColor(activeColor);
}

void TextBox::setCursorColor(const sf::Color& color) {
    cursorColor = color;
    cursor.setFillColor(color);
}

void TextBox::setSize(sf::Vector2f size) {
    background.setSize(size);
}

void TextBox::setLimit(unsigned int limit) {
    charLimit = limit;
}

std::string TextBox::getText() const {
    return displayedText.getString();
}

void TextBox::handleEvent(const sf::Event& event) {
    if (!focused)
        return;
    
    if (event.type == sf::Event::TextEntered) {
        // Przetwarzamy tylko drukowalne znaki (ASCII 32-126)
        if (event.text.unicode >= 32 && event.text.unicode < 127) {
            if (displayedText.getString().getSize() < charLimit) {
                displayedText.setString(displayedText.getString() + static_cast<char>(event.text.unicode));
                // Aktualizacja pozycji kursora – ustawiona tuż za tekstem
                cursor.setPosition(displayedText.getPosition().x + displayedText.getLocalBounds().width + 2,
                                     displayedText.getPosition().y);
            }
        }
    } else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            sf::String str = displayedText.getString();
            if (!str.isEmpty()) {
                str.erase(str.getSize() - 1);
                displayedText.setString(str);
                cursor.setPosition(displayedText.getPosition().x + displayedText.getLocalBounds().width + 2,
                                     displayedText.getPosition().y);
            }
        }
    }
}

void TextBox::update() {
    if (focused) {
        // Miganie kursora co 0.5 sekundy
        if (blinkClock.getElapsedTime().asSeconds() >= 0.5f) {
            showCursor = !showCursor;
            blinkClock.restart();
        }
    }
}

void TextBox::loseFocus() {
    focused = false;
    background.setFillColor(normalColor);
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states);
    target.draw(displayedText, states);
    if (focused && showCursor) {
        target.draw(cursor, states);
    }
}

} // namespace btn
