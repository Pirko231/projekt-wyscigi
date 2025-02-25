#include "level1.h"

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
