#include "level1.h"

Level1::Level1(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music* _music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    sf::Texture mapTxt;

    Report report;
    report.open();
    report.logMessage("Level1");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/mapLevel1.jpg"));

    report.close();
    
    this->loadLevel(mapTxt);

    //ustawianie kolizji statycznych
    sections[1].second.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{100.f,100.f}, {60.f,60.f}}));
}

/*void Level1::handleEvents(sf::Event &_event)
{
}

void Level1::update()
{
}

void Level1::display()
{
}*/
