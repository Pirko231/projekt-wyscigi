#pragma once

#include "bodyFunction.h"
#include "player.h"
#include "raport.h"

//Zbiera wspolne zachowania i obiekty
//dla kazdego poziomu. Kazdy poziom dziedziczy ta klase.
class Level : public BodyFunction
{
public:
//mysle ze na razie nie ma po co uzywac public
//wszystkie funkcje nie beda dostepne chyba ze
//zrobi sie dynamiczne rzutowanie.
//trzeba tu tylko dac konstruktory bo konstruktory nie sa dziedziczone
    Level() = delete;
    Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);

    //odbiera wiadomosci z klawiatury. Uzywac w funkcji Program::handleEvents()
    virtual void handleEvents(sf::Event& _event);
    //aktualizuje zmienne dla obecnego okna. Uzywac w funkcji Program::update()
    virtual void update();
    //wyswietla obecne okno. Uzywac w funkcji Program::display()
    virtual void display();
    bool useDefaultView() const override {return false;}
    virtual ~Level();
private:
    //miejsce na obiekty statyczne
    //----------------------------------------

    //domyslnie true, po zaladowaniu false. Wyznacza czy wczytywac statyczne obiekty
    static bool staticLoaded; 

    static sf::View gameView;

    //static std::vector<Bot> bots;

    //----------------------------------------

    //mapa rysowana w display
    sf::Sprite map;
    
    //tekstura mapy
    sf::Texture mapTexture;

    //laduje widok aby byl na samochod
    //void loadView();
    
protected:
    //laduje rzeczy takie jak tekstura dla mapy
    void loadLevel(const sf::Texture& _mapTexture);

    //funkcja ktora polega na resetowaniu poziomu czyli ustawiania samochodu
    //i botow na pozycji startowej itd. Kazda klasa dziedziczaca ma swoją wlasną implementacje
    virtual void resetLevel() {} //jeszcze bedzie wirtualna ale nie teraz/*= 0*/;

    //gracz (jako wskaznik)
    Player* player;

    //sf::Texture playerTexture;
};


