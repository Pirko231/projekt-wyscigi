#include "level.h"

Level::Level(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings}
{
}

Level::~Level()
{
}
