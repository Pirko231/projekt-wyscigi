#pragma once

#include <memory>
#include <optional>
#include <array>
#include <iostream>
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
    //wczytuje plik z danymi o najlepszych czasach
    Level(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music, std::string _timesFilename);

    // Odbiera wiadomości z klawiatury – używać w Program::handleEvents()
    virtual void handleEvents(sf::Event& _event);
    // Aktualizuje zmienne dla obecnego okna – używać w Program::update()
    virtual void update();
    // Wyświetla obecne okno – używać w Program::display()
    virtual void display();
    bool useDefaultView() const override { return false; }
    //zapisuje do pliku dane z czasem
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

    int lapAmount{3};

private:
    // Obiekty statyczne (widok gry)
    static bool staticLoaded;
    static sf::View gameView;

    // Mapa i tekstura mapy
    sf::Sprite map;
    sf::Texture mapTexture;

    // Flaga resetu poziomu
    bool shouldReset{ true };

    // Resetuje poziom – uniwersalne czynności
    void reset();

    //wywolac kiedy wyscig sie skonczy
    //void endRace();

    struct BestTime
    {
        BestTime() = default;
        BestTime(std::string _owner, sf::Time _time, sf::Time lapTime) : owner{_owner}, overallTime{_time}, bestLap{lapTime} {}
        std::string owner;
        sf::Time overallTime;
        sf::Time bestLap;
    };

    std::array<BestTime, 5> bestTimes;

    std::string timesFilename;

    class EndRace : public sf::Drawable
    {
    public:
        EndRace();
        //prawda jezeli ekran jest aktywny, falsz kiedy nie jest
        operator bool() {return this->isActive;}

        //aktywuje ekran koncowy
        void activate() {this->isActive = true;}

        //wywolac kiedy wyscig sie skonczy
        //zajmie sie ustawieniem wszystkiego na sam koniec.
        //zdobedzie czas i go ustawi
        void operator()(Level& level);

        void handleEvents(Level& level, sf::Event& ev);

        void update(Level& level);
    private:
        bool isActive{false};
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override
        {   
            target.draw(this->continueButton, states);
            target.draw(this->continueText, states);
            target.draw(this->userName, states);
            target.draw(this->userNameText, states);
        }
        sf::Font font;
        sf::Font defaultFont;

        btn::RectangleButton continueButton;
        sf::Text continueText;

        btn::TextBox userName;
        sf::Text userNameText;
    }; EndRace endRace;
};
