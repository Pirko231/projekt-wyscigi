#ifndef BODY_FUNCTION_H
#define BODY_FUNCTION_H

#include <SFML/Graphics.hpp>

//klasa wirtualna. Nie uzywac jej w kodzie. Mozna dziedziczyc.
class BodyFunction
{
public:
    BodyFunction() = delete;
    BodyFunction(sf::RenderWindow* _window);
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
};

#endif