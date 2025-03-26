#include "level3.h"

Level3::Level3(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music *_music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music, "times3.txt"}
{
    sf::Texture mapTxt;

    perf::Report report;
    report.open();
    report.logMessage("Level3");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/textures/mapLevel3.jpg"));

    report.close();
    
    this->loadLevel(mapTxt, {-320, -180});

    this->checkPoints.push_back(bdr::CheckPoint{{400.f, 400.f}, {20.f, 100.f}});
}

void Level3::resetCurrentLevel()
{
    this->player->setPosition({655.f, 682.f});
    this->player->setRotation(272.f);
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
