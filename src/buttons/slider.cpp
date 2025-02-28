#include "slider.h"

namespace btn {

    // Konstruktor - ustawia wartości początkowe
    Slider::Slider(sf::Vector2f pos, sf::Vector2f size, sf::Color lineColor, sf::Color dotColor, int* linkedValue)
        : linkedValue(linkedValue), minValue(0), maxValue(100), isDragging(false)
    {
        // Ustawienie pozycji i rozmiaru linii (paska suwaka)
        line.setPosition(pos);
        line.setSize(size);
        line.setFillColor(lineColor);

        // Ustawienie kropki (suwaka) na linii, jej promień zależy od wysokości linii
        float dotRadius = size.y * 1.5f;  // Promień kropki to 1.5 razy wysokość linii
        dot.setRadius(dotRadius);
        dot.setFillColor(dotColor);
        baseDotColor = dotColor;

        // Wyśrodkowanie kropki na linii
        dot.setOrigin(dotRadius, dotRadius);
        dot.setPosition(pos.x, pos.y + size.y / 2);

        hoverDotColor = sf::Color::White;  // Kolor kropki przy najechaniu to biały
    }

    // Ustawienie pozycji suwaka
    void Slider::setPosition(sf::Vector2f pos)
    {
        line.setPosition(pos);  // Przesunięcie linii
        dot.setPosition(pos.x, pos.y + line.getSize().y / 2);  // Przesunięcie kropki
    }

    // Zarządzanie interakcją z myszką
    bool Slider::manageHover(sf::Vector2i mousePos, bool clicked)
    {
        sf::Vector2f mouseWorldPos = static_cast<sf::Vector2f>(mousePos);  // Przekształcamy pozycję myszki do współrzędnych świata

        // Jeśli kliknięto, a kropka nie jest jeszcze przeciągana
        if (clicked) {
            if (!isDragging) {
                if (dot.getGlobalBounds().contains(mouseWorldPos))  // Jeśli myszka jest nad kropką, zaczynamy przeciąganie
                    isDragging = true;
            }

            // Jeśli kropka jest przeciągana
            if (isDragging) {
                float newX = mouseWorldPos.x;  // Nowa pozycja X kropki
                float minX = line.getPosition().x;  // Minimalna wartość X (początek linii)
                float maxX = line.getPosition().x + line.getSize().x;  // Maksymalna wartość X (koniec linii)

                // Ograniczenie kropki do granic linii
                if (newX < minX)
                    newX = minX;
                if (newX > maxX)
                    newX = maxX;

                dot.setPosition(newX, dot.getPosition().y);  // Ustawienie nowej pozycji kropki
                updateValue();  // Zaktualizowanie powiązanej wartości
            }
            return true;
        }
        else {
            isDragging = false;  // Jeśli nie kliknięto, kończymy przeciąganie
        }

        // Zmiana koloru kropki w zależności od tego, czy myszka nad nią
        dot.setFillColor(dot.getGlobalBounds().contains(mouseWorldPos) ? hoverDotColor : baseDotColor);
        return false;
    }

    // Funkcja aktualizująca wartość na podstawie pozycji kropki
    void Slider::updateValue()
    {
        float relativePos = dot.getPosition().x - line.getPosition().x;  // Odległość kropki od początku linii
        float lineWidth = line.getSize().x;  // Szerokość linii

        // Obliczenie procentowej pozycji kropki
        float percent = relativePos / lineWidth;
        if (percent < 0.f)
            percent = 0.f;  // Ograniczenie do zakresu [0,1]
        if (percent > 1.f)
            percent = 1.f;

        // Przeliczenie procentowej wartości na wartość w zakresie [minValue, maxValue]
        int value = minValue + static_cast<int>(percent * (maxValue - minValue));
        if (linkedValue)
            *linkedValue = value;  // Aktualizacja wartości podanej w konstruktorze
    }

    // Pozostałe funkcje, które pozwalają na pobranie i ustawienie parametrów suwaka
    sf::Vector2f Slider::getPosition() const
    {
        return line.getPosition();
    }

    sf::FloatRect Slider::getLocalBounds() const
    {
        return line.getLocalBounds();
    }

    sf::FloatRect Slider::getGlobalBounds() const
    {
        return line.getGlobalBounds();
    }

    void Slider::move(sf::Vector2f offset)
    {
        line.move(offset);
        dot.move(offset);
    }

    void Slider::setSize(sf::Vector2f size)
    {
        line.setSize(size);  // Ustawienie rozmiaru linii
        float dotRadius = size.y * 1.5f;  // Ustawienie rozmiaru kropki w zależności od wysokości linii
        dot.setRadius(dotRadius);
    }

    void Slider::setLineColor(sf::Color color)
    {
        line.setFillColor(color);
    }

    void Slider::setDotColor(sf::Color color)
    {
        dot.setFillColor(color);
        baseDotColor = color;
    }

    void Slider::setDotHoverColor(sf::Color color)
    {
        hoverDotColor = color;
    }

    // Rysowanie suwaka na ekranie
    void Slider::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(line, states);  // Rysowanie linii
        target.draw(dot, states);   // Rysowanie kropki
    }

} // namespace btn
