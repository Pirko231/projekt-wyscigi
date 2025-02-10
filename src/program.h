#pragma once

#include "mainMenu.h"
#include "levelSelection.h"

#include "level1.h"
#include "level2.h"
#include "level3.h"

class Program
{
public:
    Program();
    void handleEvents();
    void update();
    void display();
    bool running() const {return this->window->isOpen();}
    ~Program();
private:
    //w tym oknie renderowane beda wszystkie rzeczy
    sf::RenderWindow* window;

    //myszka (uzywana do zdobycia jej pozycji). Zeby zdobyc pozycje myszki
    //nalezy uzyc .getPosition(this->window) (zeby pozycja byla relatywna do okna)
    sf::Mouse mouse;

    //rozmiar tablicy managingFunctions
    static constexpr int managingFunctionsAmount {5};

    //obecna funkcja, dla wygody w typie wyliczeniowym aby
    //nie trzeba bylo zapamietywac zmian
    //zdefiniowane w bodyFunction.h
    ManagingFunctionsIterator currentFunction;
    

    //tablica wskaznikow do funkcji w ktorych znajdowac beda sie
    //klasy takie jak mainMenu. Wszystkie maja trzy wirtualne funkcje:
    //void handleEvents(), void update(), void display()
    //Rozmiar tablicy wynosi 'managingFunctionsAmount'
    BodyFunction* managingFunctions[managingFunctionsAmount] {nullptr, nullptr, nullptr, nullptr, nullptr};

};