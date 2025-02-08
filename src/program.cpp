#include "program.h"

Program::Program()
{
    this->window = new sf::RenderWindow;
    this->window->create({500, 500}, "Wyscigi", sf::Style::Titlebar | sf::Style::Close);
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
    }
}

void Program::update()
{
}

void Program::display()
{
    //tutaj bedzie zarzadzanie rysowaniem wszystkich rzeczy
    this->window->clear();
    //wszystko co chcemy rysowac ma sie znajdowac ponizej funkcji clear
    //tutaj beda uzywane tablice wskaznikow do funkcji
    
    //ta funkcja wyswietla na ekran narysowane rzeczy
    window->display();
}

Program::~Program()
{
    delete this->window;
}
