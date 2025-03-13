#include "level1.h"

Level1::Level1(sf::RenderWindow *_window, sf::Mouse *_mouse, ManagingFunctionsIterator &_managingFunctionsIterator, Settings *_settings, sf::Music* _music) : Level{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    sf::Texture mapTxt;

    Report report;
    report.open();
    report.logMessage("Level1");

    report.addEntry("Mapa", mapTxt.loadFromFile("resources/mapLevel1.jpg"));

    report.close();
    
    this->loadLevel(mapTxt, {-310, -198});

    //ustawianie kolizji statycznych
    sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{691.f,213.f}, {30.f,50.f}}));
    sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{736.f,154.f}, {292.f,30.f}}));
    sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{691.f,31.f}, {362.f,30.f}}));
    sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1043.f,200.f}, {30.f,180.f}}));
    sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{1169.f,162.f}, {30.f,180.f}}));

    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{32.f,100.f}, {30.f,280.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{402.f,229.f}, {152.f,30.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{365.f,354.f}, {220.f,30.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{354.f,125.f}, {30.f,80.f}}));
    sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{231.f,163.f}, {30.f,120.f}}));
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
        
        sf::Vector2f pos1{547.f, 241.f};
        sf::Vector2f pos2{732.f, 157.f};
        sf::Vector2f pos3{230.f, 105.f};
        sf::Vector2f pos4{204.f, 120.f};
        sf::Vector2f pos5{144.f, 11.f};
        sf::Vector2f pos6{256.f, 11.f};
        sf::Vector2f pos7{357.f, 200.f};
        sf::Vector2f pos8{350.f, 356.f};
        sf::Vector2f pos9{590.f, 355.f};
        sf::Vector2f pos10{683.f, 46.f};
        sf::Vector2f pos11{1024.f, 159.f};
        sf::Vector2f pos12{1054.f, 42.f};
        //zakret _| ostry
        for (int i = 0; i < 7; i++, pos1.x += 5.f, pos1.y -= 4.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos1, {15.f, 15.f}}));
        }
        //zakret |_ ostry
        for (int i = 0; i < 6; i++, pos7.x += 4.f, pos7.y += 6.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos7, {15.f, 15.f}}));
        }
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{390.f,237.f}, {15.f,15.f}}));
        //zakret |- ostry
        for (int i = 0; i < 5; i++, pos2.x -= 6.f, pos2.y += 3.f, pos3.x -= 6.f, pos3.y += 3.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos2, {15.f, 15.f}}));
        }
        for (int i = 0; i < 6; i++, pos3.x -= 6.f, pos3.y += 3.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos3, {15.f, 15.f}}));
        }
        sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{694.f,192.f}, {15.f,19.f}}));
        sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{698.f,182.f}, {15.f,15.f}}));
        sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{703.f,175.f}, {15.f,15.f}}));
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{166.f,142.f}, {15.f,15.f}}));
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{162.f,146.f}, {15.f,19.f}}));
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{158.f,152.f}, {15.f,19.f}}));
        //zakret -| ostry
        for (int i = 0; i < 6; i++, pos4.x += 6.f, pos4.y += 3.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos4, {15.f, 15.f}}));
        }
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{236.f,147.f}, {15.f,15.f}}));
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{242.f,152.f}, {15.f,15.f}}));
        //zakret |- lagodny
        for (int i = 0; i < 6; i++, pos5.x -= 8.f, pos5.y += 2.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos5, {15.f, 15.f}}));
        }
        for (int i = 0; i < 12; i++, pos5.x -= 4.f, pos5.y += 5.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos5, {15.f, 15.f}}));
        }
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{48.f,95.f}, {15.f,16.f}}));
        //inny
        for (int i = 0; i < 6; i++, pos10.x -= 8.f, pos10.y += 2.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos10, {15.f, 15.f}}));
        }
        for (int i = 0; i < 12; i++, pos10.x -= 4.f, pos10.y += 5.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos10, {15.f, 15.f}}));
        }
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{48.f,95.f}, {15.f,16.f}}));

        //zakret -| lagodny
        for (int i = 0; i < 6; i++, pos6.x += 8.f, pos6.y += 2.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos6, {15.f, 15.f}}));
        }
        for (int i = 0; i < 12; i++, pos6.x += 4.f, pos6.y += 5.f)
        {
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos6, {15.f, 15.f}}));
        }
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{351.f,95.f}, {15.f,17.f}}));
        sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{357.f,108.f}, {15.f,17.f}}));

        //zakret |_ lagdny
        for (int i = 0; i < 8; i++, pos8.x -= 8.f, pos8.y -= 3.f)
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos8, {15.f, 15.f}}));
    
        for (int i = 0; i < 9; i++, pos8.x -= 3.8f, pos8.y -= 6.f)
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos8, {15.f, 15.f}}));
        //chuj wi juz co
        //pierwsza czesc
        for (int i = 0; i < 7; i++, pos9.x += 8.f, pos9.y -= 3.f)
            sections[1].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos9, {15.f, 15.f}}));
    
        //druga czesc
        for (int i = 0; i < 9; i++, pos9.x += 5.f, pos9.y -= 7.5f){
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos9, {15.f, 15.f}}));
        }
        sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{{690.f,254.f}, {15.f,17.f}}));
        //ostry
        for (int i = 0; i < 6; i++, pos11.x += 6.f, pos11.y += 6.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos11, {15.f, 15.f}}));
        }
        //zakret -| lagodny
        for (int i = 0; i < 6; i++, pos12.x += 8.f, pos12.y += 2.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos12, {15.f, 15.f}}));
        }
        for (int i = 0; i < 8; i++, pos12.x += 6.f, pos12.y += 5.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos12, {15.f, 15.f}}));
        }
        for (int i = 0; i < 9; i++, pos12.x += 3.f, pos12.y += 7.f)
        {
            sections[0].first.push_back(std::make_unique<bdr::Rectangle>(bdr::Rectangle{pos12, {15.f, 15.f}}));
        }

    }
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

    //ustawienie checkpointow

    //pierwszy checkpoint to start i meta
    checkPoints.push_back(bdr::CheckPoint{{521.f,564.f}, {20.f, 90.f}});
    
    // Ustawienie tła licznika na pozycję: lewy górny róg (353,124) i rozmiar 244x138
    lapTimer.setBackground(sf::Vector2f(405.f, 147.f), sf::Vector2f(143.f, 78.f));


    checkPoints.push_back(bdr::CheckPoint{{65.f,150.f}, {90.f, 20.f}});
    checkPoints.push_back(bdr::CheckPoint{{720.f,564.f}, {20.f, 90.f}});
}

void Level1::resetCurrentLevel()
{
    this->player->setPosition({676.f, 636.f});
    this->player->setRotation(270.f);
}