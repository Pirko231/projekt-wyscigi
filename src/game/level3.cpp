#include "level3.h"

Level3::Level3(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings) : Level{_window, _mouse, _managingFunctionsIterator, _settings, "times3.txt"}
{
    sf::Texture mapTxt;

    perf::Report report;
    report.open();
    report.logMessage("Level3");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/textures/mapLevel3.jpg"));

    report.close();
    
    this->loadLevel(mapTxt, {-320, -180});

    //ustawienie checkpointow
    this->checkPoints.push_back(bdr::CheckPoint{{189.f, 602.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{36.f, 549.f}, {110.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{35.f, 174.f}, {110.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{159.f, 25.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{240.f, 25.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{266.f, 173.f}, {100.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{265.f, 210.f}, {100.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{394.f, 244.f}, {20.f, 120.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{849.f, 259.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{968.f, 259.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1036.f, 259.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1082.f, 200.f}, {100.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{1020.f, 43.f}, {20.f, 100.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{862.f, 184.f}, {100.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{853.f, 370.f}, {120.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{919.f, 526.f}, {120.f, 20.f}});
    this->checkPoints.push_back(bdr::CheckPoint{{863.f, 602.f}, {20.f, 110.f}});



    //meta
    this->checkPoints.push_back(bdr::CheckPoint{{493.f, 603.f}, {20.f, 100.f}});
}

void Level3::resetCurrentLevel()
{
    this->player->setPosition({655.f, 682.f});
    this->player->setRotation(272.f);
    this->player->setFriction(1.4f);
}

void Level3::checkForUnclocks(const Level::BestTime& stats)
{
    if (stats.bestLap <= sf::seconds(16.f))
        const_cast<SettingsData*>(this->settings->getData())->car3 = true;
}
