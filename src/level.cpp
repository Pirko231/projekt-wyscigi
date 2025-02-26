#include "level.h"
#include "bodyFunction.h"

typedef ManagingFunctionsIterator MFI;

Level::Level(sf::RenderWindow* wind, sf::Mouse* mouse, MFI& mfi, Settings* cfg) : BodyFunction{wind, mouse, mfi, cfg}
{
    
}

void Level::handleEvents(sf::Event &_event)
{
}

void Level::display()
{
}

void Level::update()
{
}

Level::~Level()
{
}