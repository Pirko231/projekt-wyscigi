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
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{32.f,100.f}, {30.f,280.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{32.f,100.f}, {30.f,280.f}}));

    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{220.f,535.f}, {480.f, 30.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{160.f,655.f}, {520.f, 30.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{32.f,340.f}, {30.f, 240.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{156.f,340.f}, {30.f, 180.f}}));

    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{550.f,535.f}, {480.f, 30.f}}));
    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{590.f,655.f}, {480.f, 30.f}}));
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
