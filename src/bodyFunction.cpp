#include "bodyFunction.h"

BodyFunction::BodyFunction(sf::RenderWindow *_window, ManagingFunctionsIterator& _managingFunctionsIterator) : functionIterator{_managingFunctionsIterator}
{
    this->window = _window;
}

BodyFunction::~BodyFunction()
{

}
