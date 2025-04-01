#include "program.h"

#include "util.h"

Program::Program()
{

    this->window = new sf::RenderWindow;
    this->window->create({1280, 720}, "Rizzy Roads", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    this->window->setFramerateLimit(60);

    this->mouse = new sf::Mouse;

    this->cars = new Cars;

    this->settings = new Settings{this->window, this->mouse, this->cars, this->currentFunction};

    util::MusicPlayer::init(settings);

    this->defaultView.setSize(static_cast<sf::Vector2f>(this->window->getSize()));
    this->defaultView.setCenter(this->window->getSize().x / 2, this->window->getSize().y / 2);
    this->window->setView(this->defaultView);

    // ustawnienie poczatku pracy programu na mainMenu
    this->currentFunction = ManagingFunctionsIterator::mainMenu;

    this->previousFunction = ManagingFunctionsIterator::carSelection;

    BodyFunction::initBackground();

    // kazdy z tych obiektow bedzie mial swoj wlasny obiekt typu Raport
    this->managingFunctions[0] = new MainMenu{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[1] = new LevelSelection{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[2] = new CarSelection{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[3] = new Level1{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[4] = new Level2{this->window, this->mouse, this->currentFunction, this->settings};
    this->managingFunctions[5] = new Level3{this->window, this->mouse, this->currentFunction, this->settings};

    util::updateDeltaTime();
}

void Program::handleEvents()
{
    // tutaj odbieramy wszystkie eventy takie jak:
    // nacisniecie klawisza, zamkniecie okna, klikniecie myszka
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        // to musi byc uniwersalne, a tablice wskaznikow funkcji beda
        // tez tutaj uzyte
        if (event.type == sf::Event::Closed)
            this->window->close();

        // jest tylko roboczo aby zmieniac wyswietlane funkcje. Potem usunac
        if (event.type == sf::Event::KeyPressed)
        {
            //this->arrowScreenChange(event); //wylaczone bo tylko dla developera
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
    util::updateDeltaTime();

    util::MusicPlayer::get().play();
    if (*this->settings)
    {
        this->settings->update();
        return;
    }

    this->managingFunctions[this->currentFunction]->update();

    this->settings->handleFunctionChange();
}

void Program::display()
{
    // tutaj bedzie zarzadzanie rysowaniem wszystkich rzeczy
    this->window->clear();

    // wszystko co chcemy rysowac ma sie znajdowac ponizej funkcji clear
    // tutaj beda uzywane tablice wskaznikow do funkcji

    if (this->managingFunctions[this->currentFunction]->useDefaultView())
        this->window->setView(this->defaultView);

    this->managingFunctions[this->currentFunction]->display();

    if (*this->settings)
        this->settings->display();
    

    // ta funkcja wyswietla na ekran narysowane rzeczy
    window->display();
}

Program::~Program()
{
    // usuwamy okno
    delete this->window;

    // usuwamy ustawienia
    delete this->settings;

    delete this->cars;

    // usuwamy funkcje do wyswietlania
    for (size_t i = 0; i < Program::managingFunctionsAmount; i++)
        delete this->managingFunctions[i];
}

void Program::arrowScreenChange(const sf::Event &event)
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
}
