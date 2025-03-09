#pragma once

#include <memory>

#include "bodyFunction.h"
#include "player.h"
#include "raport.h"
#include "gameObjects.h"

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
    
    //kiedy zmienna jest true to pozycja wszystkiego zostanie ustawiona na
    //'pozycje startowe'. Nalezy ustawic ją na true przy wychodzeniu z poziomu
    bool shouldReset{true};
    
protected:
    //laduje rzeczy takie jak tekstura dla mapy
    void loadLevel(const sf::Texture& _mapTexture);

    //funkcja ktora polega na resetowaniu poziomu czyli ustawiania samochodu
    //i botow na pozycji startowej itd. Kazda klasa dziedziczaca ma swoją wlasną implementacje
    virtual void resetLevel() = 0; //jeszcze bedzie wirtualna ale nie teraz/*= 0*/;

    //gracz (jako wskaznik)
    Player* player;

    //ilosc sekcji na ekran
    static constexpr int sectionAmount {4}; 
    
    //sf::Floatrect
    //obszary, koordynaty roznych stref
    //sluza do wyznaczania jaki std::vector kolizji
    //nalezy przeslac
    //std::vector
    //przechowuje obiekty do kolizji.
    //Przehcowywane są tutaj obiekty statyczne (takie ktore są ustawiane na początku gry)
    //oraz dynamiczne (takie ktore są ustawiane przy wlaczeniu poziomu).
    std::pair<std::vector<std::unique_ptr<bdr::Collidable>>, sf::FloatRect>  sections[sectionAmount];

    //pojemnik na checkpointy, ustawia sie je w kontruktorach
    //klas dziedziczacych od Level.
    //sf::floatRect to podzial na strefy zeby checkpointy tylko z jednej
    //strefy byly sprawdzane
    std::pair< std::vector<bdr::CheckPoint>, sf::FloatRect> checkPoints[sectionAmount];
};


