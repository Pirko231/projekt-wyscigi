#pragma once

#include "buttons.h"

class SettingsData;

class Settings
{
public:
    Settings(sf::RenderWindow* _window, sf::Mouse* _mouse);

    void handleEvents(sf::Event& _event);

    void update();

    void display();

    operator bool() {return this->isTurnedOn;}
    //przypisuje do ustawien czy są obecnie wlaczane
    void operator=(bool _isOn);

    const SettingsData* getData() const {return this->data;}

    ~Settings();
private:
    sf::RenderWindow* window;

    sf::Mouse* mouse;

    SettingsData* data;

    //ilosc przyciskow w tablicy 'buttons'
    static constexpr int buttonAmount {1};

    //adresy przyciskow. Uzywanie funkcji wirtualnych.
    //btn::Button* - adres do przycisku
    //sf::Vector2f - podstawowa pozycja na zaczecie animacji
    std::pair<btn::Button*, sf::Vector2f> buttons[buttonAmount];

    //zajmuje sie animacją wchodzenia i wychodzenia z okna
    class AnimationUp
    {
    public:
        //zwraca true kiedy animacja sie zaczela i false kiedy nie lub kiedy sie skonczyla
        operator bool() {return this->animation < this->maxAnimation && this->animation > 0;}
        
        //rozoczyna animacje obiektu
        void startAnimation(sf::Vector2f _currentPos, sf::Vector2f _destination);
        
        //animuje obiekt
        void operator()(Settings& _settings);
    private:
        bool animationStarted{false};

        int maxAnimation{40};
        int animation{maxAnimation};

        int framerate{60};
        sf::Vector2f moveBy;
        sf::Vector2f destination;
        sf::Vector2f currentPos;
        int speed{3};
    }; Settings::AnimationUp animation;
    
    //jezeli prawda to ustawienia beda wyswietlane. Jezeli falsz to nie beda.
    bool isTurnedOn{false};

    //tlo ustawien
    sf::RectangleShape background;

    //przycisk X ktory opuszcza ustawienia
    btn::HoweredSpriteButton x {btn::templates.getXTemplate()};

    sf::Vector2f startPos;

    sf::Vector2f destination;
};

//klasa przechowujaca dane ktore mozna ustawiac w ustawieniach.
//zeby ich uzyc nalezy zdobyc wskaznik od obiektu Settings.
class SettingsData
{
public:
    SettingsData() = default;
    int mainVolume {100};
    int musicVolume {100};
    int soundsVolume {100};
};