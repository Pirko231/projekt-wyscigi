#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow *_window) : BodyFunction{_window}
{}

void MainMenu::handleEvents(sf::Event& _event)
{
}

void MainMenu::update()
{
}

void MainMenu::display()
{
    this->window->draw(this->shape);
}

MainMenu::~MainMenu()
{
}
