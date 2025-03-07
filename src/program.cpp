#include "program.h"

Program::Program()
{
    
    this->window = new sf::RenderWindow;
    this->window->create({1280, 720}, "Wyscigi", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(60);

    this->mouse = new sf::Mouse;

    this->music = new sf::Music;

    this->cars = new Cars;

    this->defaultView.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    this->defaultView.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    this->window->setView(this->defaultView);

    //ustawnienie poczatku pracy programu na mainMenu
    this->currentFunction = ManagingFunctionsIterator::mainMenu;

    this->previousFunction = ManagingFunctionsIterator::carSelection;

    Raport raport;
    //miejsce na wczytanie rzeczy z plikow w tej funkcji
    //-------------------------------------------
    raport.open();


    raport.close();
    //-------------------------------------------

    this->settings = new Settings{this->window, this->mouse, this->cars};

    //kazdy z tych obiektow bedzie mial swoj wlasny obiekt typu Raport
    this->managingFunctions[0] = new MainMenu{this->window, this->mouse, this->currentFunction, this->settings, this->music};
    this->managingFunctions[1] = new LevelSelection{this->window, this->mouse, this->currentFunction, this->settings, this->music};
    this->managingFunctions[2] = new CarSelection{this->window, this->mouse, this->currentFunction, this->settings, this->music};
    this->managingFunctions[3] = new Level1{this->window, this->mouse, this->currentFunction, this->settings, this->music};
    this->managingFunctions[4] = new Level2{this->window, this->mouse, this->currentFunction, this->settings, this->music};
    this->managingFunctions[5] = new Level3{this->window, this->mouse, this->currentFunction, this->settings, this->music};

    /*this->managingFunctions[3] = new Level1{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[4] = new Level2{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[5] = new Level3{this->window, this->mouse, this->currentFunction, this->settings};*/
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


        //jest tylko roboczo aby zmieniac wyswietlane funkcje. Potem usunac
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Right)
            {
                if (this->currentFunction < this->managingFunctionsAmount - 1)
                    this->currentFunction = static_cast<ManagingFunctionsIterator>(static_cast<int>(this->currentFunction) + 1);
                else
                    this->currentFunction = static_cast<ManagingFunctionsIterator>(0);
            }
            if (event.key.code == sf::Keyboard::Left)
            {
                if (this->currentFunction > 0)
                    this->currentFunction = static_cast<ManagingFunctionsIterator>(static_cast<int>(this->currentFunction) - 1);
                else
                    this->currentFunction = static_cast<ManagingFunctionsIterator>(this->managingFunctionsAmount - 1);
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (*this->settings)
                    *this->settings = false;
                else
                    *this->settings = true;
            }
        }

        if (*this->settings)
            this->settings->handleEvents(event);
        else
            this->managingFunctions[this->currentFunction]->handleEvents(event);
    }
}

void Program::update()
{
    this->playMusic();
    if (*this->settings)
    {
        
        this->settings->update();
        return;
    }
    
    this->managingFunctions[this->currentFunction]->update();

    //sprawdzamy czy nie zostal zmieniony ekran. Ustawiamy widok.
    if (this->currentFunction != this->previousFunction)
    {
        this->previousFunction = this->currentFunction;
        if (this->managingFunctions[this->currentFunction]->useDefaultView())
            this->window->setView(this->defaultView);
    }
}

void Program::display()
{
    //tutaj bedzie zarzadzanie rysowaniem wszystkich rzeczy
    this->window->clear();

    //wszystko co chcemy rysowac ma sie znajdowac ponizej funkcji clear
    //tutaj beda uzywane tablice wskaznikow do funkcji

    this->managingFunctions[this->currentFunction]->display();

    if (*this->settings)
    {
        /*if (!this->managingFunctions[this->currentFunction]->useDefaultView())
            this->window->setView(this->defaultView);*/
        this->settings->display();
    }

    //ta funkcja wyswietla na ekran narysowane rzeczy
    window->display();
}

Program::~Program()
{
    //usuwamy okno
    delete this->window;

    //usuwamy ustawienia
    delete this->settings;

    delete this->music;

    delete this->cars;
    
    //usuwamy funkcje do wyswietlania
    for (size_t i = 0; i < Program::managingFunctionsAmount; i++)
        delete this->managingFunctions[i];
}

void Program::playMusic()
{
    this->music->setVolume((this->settings->getData()->mainVolume / 100.f) * (this->settings->getData()->musicVolume / 100.f) * 100.f);
    if (music->getStatus() != sf::Music::Playing) {
        music->play();
    }
}
