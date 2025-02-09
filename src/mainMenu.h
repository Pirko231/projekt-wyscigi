#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "bodyFunction.h"

class MainMenu : public BodyFunction
{
public:
    MainMenu() = delete;
    MainMenu(sf::RenderWindow* _window);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~MainMenu();
private:
    //ta przestrzen jest calkowicie dla osoby ktora pracuje nad ta funckja
    sf::RectangleShape shape{{50.f, 50.f}};
};

#endif