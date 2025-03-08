#include "level3.h"

Level3::Level3(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music *_music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    sf::Texture mapTxt;

    Report report;
    report.open();
    report.logMessage("Level3");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/Speedway.jpeg"));

    report.close();
    
    this->loadLevel(mapTxt);
}

/*void Level3::handleEvents(sf::Event &_event)
{
}

void Level3::update()
{
}

void Level3::display()
{
}*/
