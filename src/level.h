#pragma once

#include "bodyFunction.h"
#include "player.h"

//Klasa abstrakcyjna. Zbiera wspolne zachowania i obiekty
//dla kazdego poziomu. Kazdy poziom dziedziczy ta klase.
class Level : public BodyFunction
{
public:
//mysle ze na razie nie ma po co uzywac public
//wszystkie funkcje nie beda dostepne chyba ze
//zrobi sie dynamiczne rzutowanie.
//trzeba tu tylko dac konstruktory bo konstruktory nie sa dziedziczone
    Level() = delete;
    Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings);

    //odbiera wiadomosci z klawiatury. Uzywac w funkcji Program::handleEvents()
    virtual void handleEvents(sf::Event& _event) = 0;
    //aktualizuje zmienne dla obecnego okna. Uzywac w funkcji Program::update()
    virtual void update() = 0;
    //wyswietla obecne okno. Uzywac w funkcji Program::display()
    virtual void display() = 0;
    virtual ~Level();
private:
//tutaj wszystkie rzeczy ktore sa wspolne dla wszystkich leveli.
//DO OBIEKTOW PRIVATE TRZEBA UMIESCIC ACCESSOR FUNCTIONS W PUBLIC LUB PROTECTED
//np. gracz, boty itd. Jezeli cos jest wspolne to nalezy umiesic tutaj.
//mape tutaj tez najlepiej przechowywac, a w klasach dziedziczacych
//wczytywac ja po prostu z roznych plikow 

    //gracz (pojazd gracza)
    

protected:
//wszystko w tym zakresie tez bedzie dostepne dla klas dziedziczacych
//ale nie trzeba uzywac accessor functions jak w private.
    Player player;
};