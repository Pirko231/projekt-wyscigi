#include "level.h"

bool Level::staticLoaded = false;
sf::View Level::gameView{};
LapTimer Level::lapTimer{};
Level::EndRace Level::endRace{};

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music, std::string _timesFilename) : BodyFunction{ _window, _mouse, _managingFunctionsIterator, _settings, _music }
{
    this->player = this->settings->getStartingData()->player;
    this->timesFilename = _timesFilename;

    //wczytanie danych o czasach z pliku
    std::fstream file;
    file.open(this->timesFilename, std::ios::in);
    if (file.is_open())
        for (std::size_t i = 0; i < this->bestTimes.size(); i++)
        {
            std::string owner;
            std::getline(file, owner, ' ');
            std::string bestLap;
            std::getline(file, bestLap, ' ');
            std::string allTime;
            std::getline(file, allTime, '\n');
            sf::Time allTimet;
            sf::Time bestLapt;
            try
            {
                allTimet = sf::seconds(std::stof(allTime));
                bestLapt = sf::seconds(std::stof(bestLap));
            }
            catch(const std::invalid_argument& e)
            {
                std::cerr << e.what() << '\n';
                allTimet = sf::seconds(0.f);
                bestLapt = sf::seconds(0.f);
            }
            if (owner.empty())
                owner = 'x';
            if (allTimet.asSeconds() == 0)
                allTimet = sf::seconds(0.f);
            this->bestTimes[i] = Level::BestTime{owner, allTimet, bestLapt};
            //this->bestTimes.push_back({owner, time});
        }

    this->gameView.setSize(this->player->getLocalBounds().width, this->player->getLocalBounds().height);
    this->gameView.setCenter(this->player->getPosition().x / 2.f, this->player->getPosition().y / 2.f);

    // Ustawienie sekcji ekranu
    this->sections[0].second = sf::FloatRect({ static_cast<float>(this->window->getSize().x) / 2.f, 0.f },
                                             { static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2 });
    this->sections[1].second = sf::FloatRect({ 0.f, 0.f },
                                             { static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2 });
    this->sections[2].second = sf::FloatRect({ 0.f, static_cast<float>(this->window->getSize().y) / 2.f },
                                             { static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2 });
    this->sections[3].second = sf::FloatRect({ static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2.f },
                                             { static_cast<float>(this->window->getSize().x) / 2.f, static_cast<float>(this->window->getSize().y) / 2 });

    Report report;
    report.open();

    if (!Level::staticLoaded)
    {
        report.logMessage("Level static space");


        sf::Texture lapTimerTxt;
        report.addEntry("Tekstura licznik", lapTimerTxt.loadFromFile("resources/baner_timer.png"));
        Level::lapTimer.setTexture(std::move(lapTimerTxt));
        sf::Font lapTimerFont;
        report.addEntry("Czcionka licznik", lapTimerFont.loadFromFile("fonts/alarmClock.ttf"));
        Level::lapTimer.setFont(std::move(lapTimerFont));
        
        this->lapTimer.setPosition({this->window->getSize().x / 2.f - this->lapTimer.getGlobalBounds().width / 5.5f, 0.f}, {0.35f,0.35f});
        //this->lapTimer.setPosition({0.f,0.f});
        
        Level::endRace.loadFromFile(report);
        
        Level::staticLoaded = true;
    }

    report.close();
}

void Level::handleEvents(sf::Event &_event)
{
    if (this->endRace)
    {
        this->endRace.handleEvents(*this, _event);
        return;
    }

    this->player->handleEvents(_event);
}

void Level::update()
{
    if (this->settings->hasFunctionChanged())
    {
        this->reset();
        this->settings->getCars()->setPlayerNumber(this->settings->getStartingData()->carNumber);
    }

    if (this->endRace)
    {
        this->endRace.update(*this);
        return;
    }

    for (std::size_t i = 0; i < this->sectionAmount; i++)
        if (this->sections[i].second.intersects(this->player->getGlobalBounds()))
            this->player->setCollisions(&this->sections[i].first);

    this->player->update();
    if (this->player->manageCheckpoints(this->checkPoints.begin(), this->checkPoints.end(), this->lapTimer.getElapsedTime()))
        if (this->player->getLaps() >= this->lapAmount)
            this->endRace(*this);

    Level::lapTimer.setLaps(this->player->getLaps());
    Level::lapTimer.update();
    
}

void Level::display()
{
    this->gameView.setSize(static_cast<sf::Vector2f>(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2)));
    this->gameView.setCenter(this->player->getPosition());
    this->window->setView(this->gameView);

    this->window->draw(this->map);
    this->window->draw(*this->player);

    
#if HITBOXTEST
    // testy dla hitboxow checkpointow i sektorow
    sf::RectangleShape shape;
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(3.f);
    shape.setFillColor(sf::Color{255,255,255,80});
    for (std::size_t i = 0; i < this->sectionAmount; i++)
    {
        shape.setPosition(sections[i].second.getPosition());
        shape.setSize(sections[i].second.getSize());
        window->draw(shape);
    }

    shape.setOutlineThickness(2.f);
    sf::Color hitboxColors[4] = {sf::Color::White, sf::Color::Cyan, sf::Color::Yellow, sf::Color::Blue};
    for (std::size_t i = 0; i < this->sectionAmount; i++)
        for (auto & obj : this->sections[i].first)
        {
            shape.setFillColor(hitboxColors[i]);
            shape.setPosition(obj->getPosition());
            shape.setSize({obj->getLocalBounds().width, obj->getLocalBounds().height});
            this->window->draw(shape);
        }

    for (std::size_t i = 0; i < this->sectionAmount; i++)
        for (auto & obj : this->checkPoints)
        {
            shape.setFillColor(obj.isActive() ? sf::Color::Green : sf::Color::Red);
            shape.setPosition(obj.getPosition());
            shape.setSize({obj.getLocalBounds().width, obj.getLocalBounds().height});
            this->window->draw(shape);
        }
#endif
    //this->window->setView(sf::View{sf::Vector2f{static_cast<float>(this->window->getSize().x / 2), static_cast<float>(this->window->getSize().y / 2)}, static_cast<sf::Vector2f>(this->window->getSize())});
    this->window->setView(this->window->getDefaultView());
    this->window->draw(Level::lapTimer);

    if (this->endRace)
    {
        this->window->setView(sf::View{sf::Vector2f{static_cast<float>(this->window->getSize().x / 2), static_cast<float>(this->window->getSize().y / 2)}, static_cast<sf::Vector2f>(this->window->getSize())});
        this->window->draw(this->endRace);
    }
}

Level::~Level()
{
    std::fstream file;
    file.open(this->timesFilename, std::ios::out);
    if (file.is_open())
        for (auto& i : this->bestTimes)
        {
            if (i.owner.empty())
                file << 'x';
            else
                file << i.owner;
            file << ' ';
            file << i.bestLap.asSeconds();
            file << ' ';
            file << i.overallTime.asSeconds();
            file << '\n';
        }
}

void Level::reset()
{
    this->resetCurrentLevel();
    this->player->reset();
    this->player->setCheckPoints(&this->checkPoints);
    this->lapTimer.reset();
    this->lapTimer.setPosition({this->window->getSize().x / 2.f - this->lapTimer.getGlobalBounds().width / 2.f, 0.f});
    this->lapTimer.setLaps(0,3); //jakby ktos chcial mozna to przeniesc do klas dziedzicacych
    for (auto& obj : checkPoints)
        obj.reset();
}

void Level::loadLevel(const sf::Texture &_mapTexture, sf::Vector2f pos)
{
    this->mapTexture = _mapTexture;
    this->map.setTexture(this->mapTexture);
    this->map.setPosition(pos);
}

Level::EndRace::EndRace()
{
    

    this->continueButton.setSize({400.f, 90.f});
    this->continueButton.setPosition({450.f, 620.f});
    this->continueButton.setColor(sf::Color::White);
    this->continueButton.setHoverColor(sf::Color{80,80,80});

    this->continueText.setString("Kontynuuj");
    this->continueText.setFont(this->font);
    this->continueText.setPosition(540.f, 635.f);
    this->continueText.setCharacterSize(50);
    this->continueText.setFillColor(sf::Color::Black);

    this->userName.setPosition({450.f, 540.f});
    this->userName.setSize({340.f, 70.f});
    this->userName.setCharacterSize(60);
    this->userName.setLimit(9);
    this->userName.setFont(this->defaultFont);

    this->userNameText.setString("Wprowadz nick");
    this->userNameText.setPosition(450.f, 490.f);
    this->userNameText.setFont(this->font);
    this->userNameText.setFillColor(sf::Color::Black);
    this->userNameText.setCharacterSize(50);

    this->okButton.setPosition({800.f, 540.f});
    this->okButton.setScale({0.6f, 0.6f});
    
    
    sf::Vector2f pos{335.f, 120.f};

    this->resultTableTitle.setString("Tabela wynikow");
    this->resultTableTitle.setPosition(pos.x + 60.f, pos.y - 120.f);
    this->resultTableTitle.setFillColor(sf::Color::Black);
    this->resultTableTitle.setCharacterSize(75);
    this->resultTableTitle.setFont(this->font);

    this->nickame.setString("nick");
    this->nickame.setPosition(pos.x + 10.f, pos.y - 40.f);
    this->nickame.setFillColor(sf::Color::Black);
    this->nickame.setCharacterSize(40);
    this->nickame.setFont(this->font);

    this->bestLap.setString("best lap");
    this->bestLap.setPosition(pos.x + 210.f, pos.y - 40.f);
    this->bestLap.setFillColor(sf::Color::Black);
    this->bestLap.setCharacterSize(40);
    this->bestLap.setFont(this->font);

    this->overallTime.setString("calosc");
    this->overallTime.setPosition(pos.x + 410.f, pos.y - 40.f);
    this->overallTime.setFillColor(sf::Color::Black);
    this->overallTime.setCharacterSize(40);
    this->overallTime.setFont(this->font);

    for (auto& i : resultTable)
    {
        i.setFont(this->font);
        i.setPosition(pos);
        pos.y += 70.f;
    }
    
}

void Level::EndRace::loadFromFile(Report& report)
{
    //Report report;
    //report.open();
    //report.logMessage("Level::EndRace");
    report.addEntry("Napisy czcionka", this->font.loadFromFile("fonts/BigFont.ttf"));
    report.addEntry("TextBox czcionka", this->defaultFont.loadFromFile("fonts/defaultFont.ttf"));
    sf::Texture okHovered;
    sf::Texture okUnHovered;
    report.addEntry("ok - hovered", okHovered.loadFromFile("resources/checkButtonHovered.png"));
    report.addEntry("ok - unhovered", okUnHovered.loadFromFile("resources/checkButtonUnhovered.png"));
    //report.close();
    this->okButton.setTextures(okHovered, okUnHovered);
}

void Level::EndRace::operator()(Level &level)
{
    this->recentData.overallTime = level.lapTimer.getElapsedTime();
    this->recentData.bestLap = level.player->getBestLap();

    //level.reset();
    this->isActive = true;
    //this->bestLapsTimer.push_back();

    level.lapTimer.setPosition({0.f,0.f}, {0.35f,0.35f});

    for (std::size_t i = 0; i < this->resultTable.size(); i++)
    {
        this->resultTable[i].setContents(level.bestTimes[i].owner, level.bestTimes[i].bestLap, level.bestTimes[i].overallTime);
    }
}

void Level::EndRace::handleEvents(Level &level, sf::Event &ev)
{
    if (this->continueButton.manageHover(level.mouse->getPosition(*level.window), true) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!this->userName.getText().empty())
            this->recentData.owner = this->userName.getText();
        this->userName.reset();

        // std::optional<std::vector<Level::BestTime>::iterator> replace;
        std::optional<std::size_t> replace;

        for (std::size_t i = level.bestTimes.size() - 1; i > 0; i--)
        {
            if (this->recentData.overallTime.asSeconds() < level.bestTimes[i].overallTime.asSeconds() || level.bestTimes[i].overallTime.asSeconds() == 0.f)
                replace.emplace() = i;
        }
        if (this->recentData.overallTime.asSeconds() < level.bestTimes[0].overallTime.asSeconds() || level.bestTimes[0].overallTime.asSeconds() == 0.f)
            replace.emplace() = 0;
        if (this->recentData.owner.empty())
            replace.reset();

        if (replace.has_value())
        {
            std::size_t j{replace.value()};

            // tutaj trzeba bedzie przerzucic wszystkie elementy o jeden do tylu
            for (std::size_t i = level.bestTimes.size() - 1; i > j; i--)
            {
                if (i - 1 >= j)
                    level.bestTimes[i] = level.bestTimes[i - 1];
            }

            level.bestTimes[j].owner = this->recentData.owner;
            level.bestTimes[j].bestLap = this->recentData.bestLap;
            level.bestTimes[j].overallTime = this->recentData.overallTime;
        }

        level.functionIterator = ManagingFunctionsIterator::mainMenu;
        this->isActive = false;
        this->recentData.clear();
    }
    this->userName.manageHover(level.mouse->getPosition(*level.window), sf::Mouse::isButtonPressed(sf::Mouse::Left));
    if (this->userName.handleEvent(ev))
    {
        this->recentData.owner = this->userName.getText();
        this->userName.reset();
    }
    if (this->okButton.manageHover(level.mouse->getPosition(*level.window), true) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        this->recentData.owner = this->userName.getText();
        this->userName.reset();
    }
}

void Level::EndRace::update(Level& level)
{
    this->continueButton.manageHover(level.mouse->getPosition(*level.window));
    this->userName.manageHover(level.mouse->getPosition(*level.window));
    this->okButton.manageHover(level.mouse->getPosition(*level.window));
}
