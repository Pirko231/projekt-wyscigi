#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "settings.h"


//klasa wirtualna. Uzywac w kodzie tylko na zasadach polimorfizmu.
class BodyFunction
{
public:
    BodyFunction() = delete;
    BodyFunction(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);
    //odbiera wiadomosci z klawiatury. Uzywac w funkcji Program::handleEvents()
    virtual void handleEvents(sf::Event& _event) = 0;
    //aktualizuje zmienne dla obecnego okna. Uzywac w funkcji Program::update()
    virtual void update() = 0;
    //wyswietla obecne okno. Uzywac w funkcji Program::display()
    virtual void display() = 0;
    //zwraca czy klasa uzywa podstawowego widoku.
    //jezeli jakas klasa nie uzywa to nalezy zdefiniowac
    //funkcje o tej samej nazwie ktora zwraca false.
    virtual bool useDefaultView() const {return true;}

    static void initBackground();

    virtual ~BodyFunction();
private:
    //podstawowy widok aplikacji
    //static sf::View defaultView;
    //static bool viewLoaded;
protected:
    //wskaznik do okna, przypisany za pomoca konstruktora
    sf::RenderWindow* window;

    //wskaznik do myszy, przypisany za pomoca konstruktora
    sf::Mouse* mouse;

    //wskaznik do ustawien. Mozna ustawiac ze jest wyswietalny za pomcoa operatora =
    Settings* settings;

    //wskaznik do muzyki. Muzyke mozna tutaj zmieniac i jest wspolna dla wszystkich klas.
    sf::Music* music;

    //zmienienie tego zmieni obecnie dzialajaca funkcje z tablicy.
    //jest to referencja do obiektu 'Program::currentFunction'.
    ManagingFunctionsIterator& functionIterator;

    static sf::Sprite backgroundSprite;

    static sf::Texture backgroundTexture;
};