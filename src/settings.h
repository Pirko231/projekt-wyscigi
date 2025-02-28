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

    //adresy przyciskow. Uzywac funkcji wirtualnych. Przypisac w konstruktorze.
    //btn::Button* - adres do przycisku
    //sf::Vector2f - podstawowa pozycja na zaczecie animacji
    std::pair<btn::Button*, sf::Vector2f> buttons[buttonAmount];

    //zajmuje sie animacją wchodzenia i wychodzenia z okna
    class AnimationUp
    {
    public:
        //zwraca true kiedy animacja sie zaczela i false kiedy nie lub kiedy sie skonczyla
        operator bool() {return this->animation < this->maxAnimation /*&& this->animation > 0*/;}

        //jezeli obecnie trwa animacja przycisku w gore to zwraca true, w przeciwnym razie false
        bool animationDown() const {return this->moveBy.y > 0;}
               
        //rozoczyna animacje obiektu
        void startAnimation(sf::Vector2f _currentPos, sf::Vector2f _destination);
        
        //animuje obiekt
        void operator()(Settings& _settings);

        //resetuje wszystkie zmienne i przygotowuje obiekt do kolejnego uzycia
        void reset();
    private:
        bool animationStarted{false};

        //maksymalna ilosc klatek ile bedzie trwala animacja
        int maxAnimation{40};
        //ile klatek bedzie jeszcze trwala animacja. wspolpracuje z maxAnimation
        int animation{maxAnimation};

        //ilosc klatek na sekunde
        int framerate{60};
        //wektor przesuniecia na kazdą klatke
        sf::Vector2f moveBy;
        //pozycja na ktora ma dostac sie obiekt. wylicza moveBy razem z currentPos
        sf::Vector2f destination;
        //pozycja na ktorej startuje obiekt. wylicza moveBy razem z destination
        sf::Vector2f currentPos;
        //modyfikator predkosci animacji
        int speed{2}; //3
    }; Settings::AnimationUp animation;
    
    //jezeli prawda to ustawienia beda wyswietlane. Jezeli falsz to nie beda.
    bool isTurnedOn{false};
    //jezeli zmienna jest prawda to ustawienia beda sie powoli wylaczaly
    bool quitting{false};
    //funkcja operator bool zapisuje tutaj jaka byla ostatnia wgrywana wartosc
    bool lastTurnedOn{false};

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