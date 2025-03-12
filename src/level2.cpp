#include "level2.h"

Level2::Level2(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music *_music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music, "times2.txt"}
{
    sf::Texture mapTxt;

    Report report;
    report.open();
    report.logMessage("Level2");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/mapLevel2.jpg"));

    report.close();
    
    this->loadLevel(mapTxt, {-275, -260});

    this->checkPoints.push_back(bdr::CheckPoint{{400.f, 400.f}, {20.f, 100.f}});
}

void Level2::resetCurrentLevel()
{
    this->player->setPosition({735.f, 670.f});
    this->player->setRotation(272.f);
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
