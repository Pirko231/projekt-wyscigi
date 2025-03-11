#include "level.h"

bool Level::staticLoaded = false;
sf::View Level::gameView{};

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    this->player = this->settings->getStartingData()->player;
    //this->player->setCollisions(&this->collisions); //pozniej bedzie wiele sektorow

    //FIX rozmiar okna nie zmienia sie zaleznie od rozmiaru gracza
    this->gameView.setSize(this->player->getLocalBounds().width, this->player->getLocalBounds().height);
    //this->gameView.setSize(static_cast<float>(this->window->getSize().x / 3), static_cast<float>(this->window->getSize().y / 3));
    this->gameView.setCenter(this->player->getPosition().x / 2.f, this->player->getPosition().y / 2.f);
    
    //ustawienie obszarow w odpowiednim ulozeniu.
    //ustwiane są tak jak uklad wspolrzednych na matematyce
    //pierwsza cwiartka jest w prawym gornym rogu.
    this->sections[0].second = sf::FloatRect{{static_cast<float>(this->window->getSize().x) / 2.f, 0.f}, {static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y / 2)}};
    this->sections[1].second = sf::FloatRect{{0.f,0.f}, {static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y / 2)}};
    this->sections[2].second = sf::FloatRect{{0.f, static_cast<float>(this->window->getSize().y) / 2.f}, {static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y / 2)}};
    this->sections[3].second = sf::FloatRect{{static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2.f}, {static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y / 2)}};

    
    Report report;
    report.open();

    //obiekty dla kazdego pliku osobno
    //na ten moment auto ale pewnie sie przeniesie gdzie indziej
    //(projekt w drodze)
    //ta strefa bedzie uzywala logMessage z konsruktora klasy dziedziczącej

    sf::Texture playerTexture;
    report.addEntry("tekstura auta", playerTexture.loadFromFile("resources/compact_blue.png"));

    //obiekty statycznie, tylko raz na dzialanie programu
    if (!Level::staticLoaded)
    {
        report.logMessage("Level static space");

    
        Level::staticLoaded = true;
    }
    
    
    report.close();
    
    
    this->player->setTexture(playerTexture);
}

void Level::handleEvents(sf::Event &_event)
{
    this->player->handleEvents(_event);
}

void Level::update()
{
    if (this->settings->hasFunctionChanged())
        this->shouldReset = true;
    //reset poziomu na start gry
    if (this->shouldReset)
    {
        this->reset();
        this->shouldReset = false;
        this->settings->getCars()->setPlayerNumber(this->settings->getStartingData()->carNumber);
        //this->settings->getStartingData()->carNumber;
    }


    //tutaj sprawdzenie w jakiej sekcji jest gracz i przeslanie odpowiedniego wskaznika
    for (std::size_t i = 0; i < this->sectionAmount; i++)
        if (this->sections[i].second.intersects(this->player->getGlobalBounds()))
            this->player->setCollisions(&this->sections[i].first);
    
    this->player->update();

    //sprawdzenie checkpointow
    //this->checkCheckpoints();

    this->player->manageCheckpoints(this->checkPoints.begin(), this->checkPoints.end());

    //sprawdzanie ukonczenia toru
    /*bool isInactive{false};
    for (std::size_t i = 0; i < this->sectionAmount; i++)
    {
        for (auto& checkPoint : checkPoints)
        {
            if (!checkPoint.isActive())
            {
                isInactive = true;
                break;
            }
        }
        if (isInactive)
            break;
        else if (i == this->sectionAmount - 1)
        {
            this->loops++;
            for (std::size_t i = 0; i < this->sectionAmount; i++)
                for (auto& checkPoint : checkPoints)
                    checkPoint.reset();
        }
            
    }*/
            
}

void Level::display()
{
    //widok wrzucimy tutaj aby sie lepiej udpdatowal
    this->gameView.setSize(static_cast<sf::Vector2f>(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2)));
    this->gameView.setCenter(this->player->getPosition());
    this->window->setView(this->gameView);


    this->window->draw(this->map);
    this->window->draw(*this->player);

    
    //przestrzen testow - aby zaczac testowac nalezy odkomentowac
    //----------------------------------------------------------------------------------

     //----miejsce do odkomentowania - na koniec testow wykomentowac
    //testy sektorow
    sf::RectangleShape shape; //wiem ze duzo kopiowania ale tylko do testow, ustawiopne lokalnie aby nie przeszkadalo
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(3.f);
    shape.setFillColor(sf::Color{255,255,255, 80});
    for (std::size_t i = 0; i < this->sectionAmount; i++)
    {
        shape.setPosition(sections[i].second.getPosition());
        shape.setSize(sections[i].second.getSize());
        window->draw(shape);
    }

    //testy hitboxow
    shape.setOutlineThickness(2.f);
    sf::Color hitboxColors[4] {sf::Color::White, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Blue};
    for (std::size_t i = 0; i < this->sectionAmount; i++)
        for (auto & obj : this->sections[i].first)
        {
            shape.setFillColor(hitboxColors[i]);
            shape.setPosition(obj->getPosition());
            shape.setSize({obj->getLocalBounds().width, obj->getLocalBounds().height});
            this->window->draw(shape);
        }

    //testy checkpointow
    for (std::size_t i = 0; i < this->sectionAmount; i++)
        for (auto & obj : this->checkPoints)
        {
            if (obj.isActive())
                shape.setFillColor(sf::Color::Green);
            else
                shape.setFillColor(sf::Color::Red);
            shape.setPosition(obj.getPosition());
            shape.setSize({obj.getLocalBounds().width, obj.getLocalBounds().height});
            this->window->draw(shape);
        }
     //- miejsce do odkomentowania. Pod koniec testow nalezy wykomentowac
    //--------------------------------------------------------------------------------
}



Level::~Level()
{
}

void Level::reset()
{
    this->resetCurrentLevel();

    this->player->reset();

    this->player->setCheckPoints(&this->checkPoints);

    this->loops = 0;

    for (std::size_t i = 0; i < this->sectionAmount; i++)
        for (auto& obj : checkPoints)
            obj.reset();
}

void Level::checkCheckpoints()
{
    //sprawdzenie checkpointow
    /*for (std::size_t i = 0; i < this->sectionAmount; i++)
        if (this->checkPoints[i].second.intersects(this->player->getGlobalBounds()))
        {
            for (int j = 0; j < checkPoints[i].first.size(); j++)
                if (this->player->getGlobalBounds().intersects(checkPoints[i].first[j].getGlobalBounds()))
                    if (j > 0 && this->checkPoints[i].first[j - 1].isActive())
                        checkPoints[i].first[j].activate();
                    else if (j == 0 && i > 0)
                        checkPoints[i - 1].first[j].activate();
                    else if (i == 0)
                        checkPoints[i].first[0].activate();
        }*/
}

void Level::loadLevel(const sf::Texture &_mapTexture)
{
    this->mapTexture = _mapTexture;
    this->map.setTexture(this->mapTexture);
}
