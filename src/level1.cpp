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
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{402.f,229.f}, {152.f,30.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{385.f,354.f}, {200.f,30.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{354.f,125.f}, {30.f,80.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{231.f,163.f}, {30.f,97.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{156.f,163.f}, {30.f,180.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{565.f,128.f}, {30.f,90.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{158.f,8.f}, {98.f,15.f}}));

    //sciany
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{220.f,535.f}, {480.f, 30.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{160.f,655.f}, {520.f, 30.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{32.f,340.f}, {30.f, 240.f}}));
    sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{156.f,340.f}, {30.f, 180.f}}));

    //zakret wewnatrz
    {
        sf::Vector2f pos {205.f, 546.f};
        for (int i = 0; i < 5; i++, pos.x -= 7.f, pos.y -= 3.f)
            sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
        for (int i = 0; i < 2; i++, pos.x -= 5.5f, pos.y -= 7.5f)
            sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
    }

    //zakret od zewnatrz
    {
        sf::Vector2f pos {144.f, 655.5f};
        for (int i = 0; i < 8; i++, pos.x -= 8.f, pos.y -= 3.f)
            sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
    
        for (int i = 0; i < 9; i++, pos.x -= 3.8f, pos.y -= 6.f)
            sections[2].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
    }
    
    //sciany
    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{550.f,535.f}, {480.f, 30.f}}));
    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{590.f,655.f}, {480.f, 30.f}}));
    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1170.f,315.f}, {30.f, 350.f}}));
    sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1043.f,255.f}, {30.f, 280.f}}));

    //zakret od wewnatrz
    {
        //sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1023.f,548.f}, {15.f, 15.f}}));
        //sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1028.f,543.f}, {15.f, 15.f}}));
        sf::Vector2f pos{1023.f, 548.f};
        for (int i = 0; i < 6; i++, pos.x += 6.f, pos.y -= 4.f)
        {
            sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
        }
    }
    //zakret od zewnatrz
    {
        sf::Vector2f pos {1073.f, 653.f};
        //pierwsza czesc
        for (int i = 0; i < 7; i++, pos.x += 8.f, pos.y -= 3.f)
            sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
    
        //druga czesc
        for (int i = 0; i < 9; i++, pos.x += 5.f, pos.y -= 7.5f)
            sections[3].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos, {15.f, 15.f}}));
    }
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
