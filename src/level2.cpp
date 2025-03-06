#include "level2.h"

Level2::Level2(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music *_music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    sf::Texture mapTxt;

    Report report;
    report.open();
    report.logMessage("Level2");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/SPEEDWAY2.0..jpg"));

    report.close();
    
    this->loadLevel(mapTxt);
}

/*void Level2::handleEvents(sf::Event &_event)
{
}

void Level2::update()
{
}

void Level2::display()
{
}*/
