#include "bodyFunction.h"

BodyFunction::BodyFunction(sf::RenderWindow *_window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator) : functionIterator{_managingFunctionsIterator}
{
    this->window = _window;
    this->mouse = _mouse;
}

BodyFunction::~BodyFunction()
{

}
