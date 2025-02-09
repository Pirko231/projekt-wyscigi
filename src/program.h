#ifndef PROGRAM_H
#define PROGRAM_H

#include "mainMenu.h"
#include "levelSelection.h"

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

    //rozmiar tablicy managingFunctions
    static constexpr int managingFunctionsAmount {2};

    

    //obecna funkcja, dla wygody w typie wyliczeniowym aby
    //nie trzeba bylo zapamietywac zmian
    //zdefiniowane w bodyFunction.h
    ManagingFunctionsIterator currentFunction;
    

    //tablica wskaznikow do funkcji w ktorych znajdowac beda sie
    //klasy takie jak mainMenu. Wszystkie maja trzy wirtualne funkcje:
    //void handleEvents(), void update(), void display()
    //Rozmiar tablicy wynosi 'managingFunctionsAmount'
    BodyFunction* managingFunctions[managingFunctionsAmount] {nullptr, nullptr};

};

#endif