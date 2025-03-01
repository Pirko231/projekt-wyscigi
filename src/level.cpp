#include "level.h"
#include "bodyFunction.h"

typedef ManagingFunctionsIterator MFI;

Level::Level(sf::RenderWindow* wind, sf::Mouse* _mouse , MFI& mfi, Settings* cfg, sf::Music* _music) : BodyFunction{wind, mouse, mfi, cfg, _music}
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