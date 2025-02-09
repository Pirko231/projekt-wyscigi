#ifndef BODY_FUNCTION_H
#define BODY_FUNCTION_H

#include <SFML/Graphics.hpp>

//Kazdy element tego typu wyliczeniowego to indeks
//pozycji w tablicy 'managingFunctions' dla danego typu
//np. na indekse numer 0 znajduje sie obiekt typu 'MainMenu'
enum ManagingFunctionsIterator
{
    mainMenu = 0,
    levelSelection  = 1
};

//klasa wirtualna. Uzywac w kodzie tylko na zasadach polimorfizmu.
class BodyFunction
{
public:
    BodyFunction() = delete;
    BodyFunction(sf::RenderWindow* _window, ManagingFunctionsIterator& _managingFunctionsIterator);
    //odbiera wiadomosci z klawiatury. Uzywac w funkcji Program::handleEvents()
    virtual void handleEvents(sf::Event& _event) = 0;
    //aktualizuje zmienne dla obecnego okna. Uzywac w funkcji Program::update()
    virtual void update() = 0;
    //wyswietla obecne okno. Uzywac w funkcji Program::display()
    virtual void display() = 0;
    virtual ~BodyFunction();
protected:
    //wskaznik do okna, przypisany za pomoca konstruktora
    sf::RenderWindow* window;

    //zmienienie tego zmieni obecnie dzialajaca funkcje z tablicy.
    //jest to referencja do obiektu 'Program::currentFunction'.
    ManagingFunctionsIterator& functionIterator;
};



#endif