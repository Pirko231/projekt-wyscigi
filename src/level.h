#pragma once

#include <memory>
#include "bodyFunction.h"
#include "player.h"
#include "raport.h"
#include "gameObjects.h"
#include "gameObjects/lapTimer.h"  // Dołączenie klasy LapTimer

// Zbiera wspólne zachowania i obiekty dla każdego poziomu.
// Każdy poziom dziedziczy tę klasę.
class Level : public BodyFunction
{
public:
    Level() = delete;
    Level(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);

    // Odbiera wiadomości z klawiatury – używać w Program::handleEvents()
    virtual void handleEvents(sf::Event& _event);
    // Aktualizuje zmienne dla obecnego okna – używać w Program::update()
    virtual void update();
    // Wyświetla obecne okno – używać w Program::display()
    virtual void display();
    bool useDefaultView() const override { return false; }
    virtual ~Level();

protected:
    // Funkcja resetująca poziom – implementacja w klasach dziedziczących
    virtual void resetCurrentLevel() = 0;

    // Ładuje teksturę mapy
    void loadLevel(const sf::Texture& _mapTexture, sf::Vector2f pos = {0.f,0.f});

    // Gracz (wskaźnik)
    Player* player;
    // Ilość sekcji na ekran
    static constexpr int sectionAmount {4};
    // Sekcje ekranu: pierwszy element pary – obiekty kolizji, drugi – obszar (sf::FloatRect)
    std::pair<std::vector<std::unique_ptr<bdr::Collidable>>, sf::FloatRect> sections[sectionAmount];
    // Checkpointy
    std::vector<bdr::CheckPoint> checkPoints;

    //licznik okrazen
    sf::Font lapTimerFont;
    LapTimer lapTimer{lapTimerFont, 30};

private:
    // Obiekty statyczne (widok gry)
    static bool staticLoaded;
    static sf::View gameView;

    // Mapa i tekstura mapy
    sf::Sprite map;
    sf::Texture mapTexture;

    // Resetuje poziom – uniwersalne czynności
    void reset();
};
