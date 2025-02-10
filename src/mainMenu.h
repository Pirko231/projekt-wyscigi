#pragma once

#include "bodyFunction.h"

class MainMenu : public BodyFunction
{
public:
    MainMenu() = delete;
    MainMenu(sf::RenderWindow* _window, ManagingFunctionsIterator& _managingFunctionsIterator);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~MainMenu();
private:
    //ta przestrzen jest calkowicie dla osoby ktora pracuje nad ta funckja
    sf::RectangleShape shape{{50.f, 50.f}};
};