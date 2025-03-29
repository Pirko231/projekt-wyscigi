#include "level2.h"

Level2::Level2(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music *_music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music, "times2.txt"}
{
    sf::Texture mapTxt;

    perf::Report report;
    report.open();
    report.logMessage("Level2");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/textures/mapLevel2.jpg"));

    report.close();
    
    this->loadLevel(mapTxt, {-320, -180});
    //ustawienie checkpoint
    this->checkPoints.push_back(bdr::CheckPoint{{470.f, 609.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{288.f, 528.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{170.f, 458.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{40.f, 370.f}, {120.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{97.f, 257.f}, {120.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{164.f, 127.f}, {120.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{324.f, 15.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{470.f, 53.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{622.f, 60.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{995.f, 58.f}, {20.f, 110.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1048.f, 185.f}, {110.f, 10.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1048.f, 235.f}, {110.f, 10.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1018.f, 269.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{774.f, 280.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{518.f, 284.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{398.f, 405.f}, {100.f, 10.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{510.f, 445.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1024.f, 453.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1063.f, 568.f}, {100.f, 10.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1024.f, 610.f}, {20.f, 100.f}});
    //meta
    this->checkPoints.push_back(bdr::CheckPoint{{585.f, 610.f}, {20.f, 100.f}});
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
