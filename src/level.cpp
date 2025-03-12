#include "level.h"

bool Level::staticLoaded = false;
sf::View Level::gameView{};

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music)
    : BodyFunction{ _window, _mouse, _managingFunctionsIterator, _settings, _music }
{
    this->player = this->settings->getStartingData()->player;

    // Ustawienie widoku gry (bazując na pozycjach gracza)
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

    // Ładowanie tekstury dla gracza
    sf::Texture playerTexture;
    report.addEntry("tekstura auta", playerTexture.loadFromFile("resources/compact_blue.png"));
    report.addEntry("Czcionka licznik", lapTimerFont.loadFromFile("fonts/alarmClock.ttf"));

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

    if (this->shouldReset)
    {
        this->reset();
        this->shouldReset = false;
        this->settings->getCars()->setPlayerNumber(this->settings->getStartingData()->carNumber);
    }

    for (std::size_t i = 0; i < this->sectionAmount; i++)
        if (this->sections[i].second.intersects(this->player->getGlobalBounds()))
            this->player->setCollisions(&this->sections[i].first);

    this->player->update();
    this->player->manageCheckpoints(this->checkPoints.begin(), this->checkPoints.end());

    // Aktualizacja licznika
    lapTimer.update();
}

void Level::display()
{
    // widok
    this->gameView.setSize(static_cast<sf::Vector2f>(sf::Vector2i(this->window->getSize().x / 2, this->window->getSize().y / 2)));
    this->gameView.setCenter(this->player->getPosition());
    this->window->setView(this->gameView);

    this->window->draw(this->map);
    this->window->draw(*this->player);

    this->window->draw(lapTimer);

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
}

Level::~Level()
{
}

void Level::reset()
{
    this->resetCurrentLevel();
    this->player->reset();
    this->player->setCheckPoints(&this->checkPoints);
    this->lapTimer.reset();
    for (auto& obj : checkPoints)
        obj.reset();
}

void Level::loadLevel(const sf::Texture &_mapTexture, sf::Vector2f pos)
{
    this->mapTexture = _mapTexture;
    this->map.setTexture(this->mapTexture);
    this->map.setPosition(pos);
}
