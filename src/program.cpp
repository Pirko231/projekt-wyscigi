#include "program.h"

Program::Program()
{
    this->window = new sf::RenderWindow;
    this->window->create({500, 500}, "Wyscigi", sf::Style::Titlebar | sf::Style::Close);

    //ustawnienie poczatku pracy programu na mainMenu
    this->currentFunction = ManagingFunctionsIterator::mainMenu;

    this->managingFunctions[0] = new MainMenu{this->window};
    this->managingFunctions[1] = new LevelSelection{this->window};
}

void Program::handleEvents()
{
    //tutaj odbieramy wszystkie eventy takie jak:
    //nacisniecie klawisza, zamkniecie okna, klikniecie myszka
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        //to musi byc uniwersalne, a tablice wskaznikow funkcji beda
        //tez tutaj uzyte
        if (event.type == sf::Event::Closed)
            this->window->close();

        this->managingFunctions[this->currentFunction]->handleEvents(event);
    }
}

void Program::update()
{
    this->managingFunctions[this->currentFunction]->update();
}

void Program::display()
{
    //tutaj bedzie zarzadzanie rysowaniem wszystkich rzeczy
    this->window->clear();

    //wszystko co chcemy rysowac ma sie znajdowac ponizej funkcji clear
    //tutaj beda uzywane tablice wskaznikow do funkcji
    this->managingFunctions[this->currentFunction]->display();
    
    //ta funkcja wyswietla na ekran narysowane rzeczy
    window->display();
}

Program::~Program()
{
    //usuwamy okno
    delete this->window;
    //usuwamy funkcje do wyswietlania
    for (size_t i = 0; i < Program::managingFunctionsAmount; i++)
        delete this->managingFunctions[i];
}
