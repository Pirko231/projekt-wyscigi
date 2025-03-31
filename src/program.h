#pragma once

#include "game/mainMenu.h"
#include "game/levelSelection.h"
#include "game/carSelection.h"

#include "game/level1.h"
#include "game/level2.h"
#include "game/level3.h"

#include "raport.h"
#include "musicPlayer.h"


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
    sf::Mouse* mouse;

    //przechowywane auta
    Cars* cars;

    //podstawowy widok aplikacji
    sf::View defaultView;

    //wywolywane w update, gra muzyke.
    //reaguje na glosnosc muzyki i kontaktuje sie z ustawieniami
    void playMusic();

    //rozmiar tablicy managingFunctions
    static constexpr int managingFunctionsAmount {6};

    //obecna funkcja, dla wygody w typie wyliczeniowym aby
    //nie trzeba bylo zapamietywac zmian
    //zdefiniowane w bodyFunction.h
    ManagingFunctionsIterator currentFunction;

    //zapamietujemy jaka byla poprzdnia funkcja aby moc sprawdzic
    //czy ekran sie zmienil.
    ManagingFunctionsIterator previousFunction;
    

    //tablica wskaznikow do funkcji w ktorych znajdowac beda sie
    //klasy takie jak mainMenu. Wszystkie maja trzy wirtualne funkcje:
    //void handleEvents(), void update(), void display()
    //Rozmiar tablicy wynosi 'managingFunctionsAmount'
    BodyFunction* managingFunctions[managingFunctionsAmount] {nullptr, nullptr, nullptr, nullptr, nullptr};

    //ekran ustawien. Aby wyswietlic trzeba uzyc przeladowanego operatora konwersji w instrukcji if
    //do uzycia uzywac update, display, handlEevents
    //mozna modyfikowac czy jest wlaczany za pomoca operatora =
    Settings* settings {nullptr};

    void arrowScreenChange(const sf::Event& event);
};

//sluzy tylko do czyszczenia danych z pliku. zdefiniowana w 'program.h'
class BootManager
{
public:
    inline BootManager()
    {this->clearBootLog();}
    //usuwa wszystkie entries w pliku bootLog.txt. zdefiniowana w 'program.h'
private:
    inline void clearBootLog()
    {
        std::fstream file("bootLog.txt", std::ios::out);
        file << "BootLog Cleared\n";
        file.close();
    }
};

inline BootManager clearBootLog;