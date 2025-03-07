#include "level.h"

bool Level::staticLoaded = false;
sf::View Level::gameView{};

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    this->player = this->settings->getStartingData()->player;

    //FIX rozmiar okna nie zmienia sie zaleznie od rozmiaru gracza
    this->gameView.setSize(this->player->getLocalBounds().width, this->player->getLocalBounds().height);
    //this->gameView.setSize(static_cast<float>(this->window->getSize().x / 3), static_cast<float>(this->window->getSize().y / 3));
    this->gameView.setCenter(this->player->getPosition().x / 2.f, this->player->getPosition().y / 2.f);

    //this->window->setView(this->gameView);
    
    Report report;
    report.open();

    //obiekty dla kazdego pliku osobno
    //na ten moment auto ale pewnie sie przeniesie gdzie indziej
    //(projekt w drodze)
    //ta strefa bedzie uzywala logMessage z konsruktora klasy dziedziczącej

    sf::Texture playerTexture;
    report.addEntry("tekstura auta", playerTexture.loadFromFile("resources/compact_blue.png"));

    //obiekty statycznie, tylko raz na dzialanie programu
    if (!Level::staticLoaded)
    {
        report.logMessage("Level static space");

    
        Level::staticLoaded = true;
    }
    
    
    report.close();
    
    
    this->player->setTexture(playerTexture);
}

void Level::handleEvents(sf::Event &_event)
{
    this->player->handleEvents(_event);
}

void Level::display()
{
    //widok wrzucimy tutaj aby sie lepiej udpdatowal
    this->window->setView(this->gameView);
    this->window->draw(this->map);
    this->window->draw(*this->player);
}

void Level::update()
{
    this->player->update();

    this->gameView.setSize(static_cast<sf::Vector2f>(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2)));
    this->gameView.setCenter(this->player->getPosition());
    //rotacja zbyt szarpie ekranem na razie to wykomentuje
    //this->gameView.setRotation(this->player->getRotation());
    //this->window->setView(this->gameView);
}

Level::~Level()
{
}

void Level::loadLevel(const sf::Texture &_mapTexture)
{
    this->mapTexture = _mapTexture;
    this->map.setTexture(this->mapTexture);
}
