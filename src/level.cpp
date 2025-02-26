#include "level.h"
#include "bodyFunction.h"

typedef ManagingFunctionsIterator MFI;

Level::Level(sf::RenderWindow* wind, sf::Mouse* mouse, MFI& mfi, Settings* cfg) : BodyFunction{wind, mouse, mfi, cfg}
{
    
}

Level::~Level()
{
}

Level1::Level1(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : Level{_window, _mouse, _managingFunctionsIterator, _settings}
{
}

void Level1::handleEvents(sf::Event &_event)
{
}

void Level1::update()
{
}

void Level1::display()
{
    this->window->draw(this->player);
}

Level2::Level2(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : Level{_window, _mouse, _managingFunctionsIterator, _settings}
{
}

void Level2::handleEvents(sf::Event &_event)
{
}

void Level2::update()
{
}

void Level2::display()
{
}

Level3::Level3(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : Level{_window, _mouse, _managingFunctionsIterator, _settings}
{
}

void Level3::handleEvents(sf::Event &_event)
{
}

void Level3::update()
{
}

void Level3::display()
{
}
