#include "level2.h"

Level2::Level2(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings) : Level{_window, _mouse, _managingFunctionsIterator, _settings, "times2.txt"}
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
    this->player->setFriction(40.f);
}

void Level2::checkForUnclocks(const Level::BestTime& stats)
{
    //daloby sie uniknac const_cast ale trzeba byloby dodawac nowe publiczne funkcje
    //ktorych ktos moglby uzyc wiec mysle ze bezpieczniej bedzie tak zrobic
    if (stats.overallTime <= sf::seconds(36.f))
        const_cast<SettingsData*>(this->settings->getData())->level3 = true;
    if (stats.bestLap <= sf::seconds(13.f))
        const_cast<SettingsData*>(this->settings->getData())->car2 = true;
}
