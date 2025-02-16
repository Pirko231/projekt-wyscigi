#include "level.h"

Level::Level(sf::RenderWindow *_window, sf::Mouse* _mouse, ManagingFunctionsIterator &_managingFunctionsIterator) : BodyFunction{_window, _mouse, _managingFunctionsIterator}
{
}

Level::~Level()
{
}
