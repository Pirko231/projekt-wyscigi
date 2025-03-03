#include "level.h"

bool Level::staticLoaded = false;
Player Level::player;

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : BodyFunction{_window, mouse, _managingFunctionsIterator, _settings, _music}
{
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
    
    
    this->player.setTexture(playerTexture);
}

void Level::handleEvents(sf::Event &_event)
{
    this->player.handleInput(_event);
}

void Level::display()
{
    this->window->draw(this->map);
    this->window->draw(this->player);
}

void Level::update()
{
}

Level::~Level()
{
}

void Level::loadLevel(const sf::Texture &_mapTexture)
{
    this->mapTexture = _mapTexture;
    this->map.setTexture(this->mapTexture);
}
