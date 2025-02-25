#include "bodyFunction.h"

BodyFunction::BodyFunction(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : functionIterator{_managingFunctionsIterator}
{
    this->window = _window;
    this->mouse = _mouse;
    this->settings = _settings;
}

BodyFunction::~BodyFunction()
{

}
