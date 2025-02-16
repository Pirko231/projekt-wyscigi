#pragma once

#include "bodyFunction.h"

class CarSelection : public BodyFunction
{
public:
    CarSelection() = delete;
    CarSelection(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~CarSelection();

private:

};