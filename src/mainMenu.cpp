#include "mainMenu.h"
#include "raport.h"

MainMenu::MainMenu(sf::RenderWindow *_window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator) : BodyFunction{_window, _mouse, _managingFunctionsIterator}
{
    Raport raport;
    raport.open();
    raport.logMessage("MainMenu");
    raport.addEntry("Wczytywanie czcionki" , this->font.loadFromFile("fonts/BigFont.ttf"));
    raport.close();

    this->button.setFont(font);
    this->button.setString("Gyat");
}

void MainMenu::handleEvents(sf::Event& _event)
{
}

void MainMenu::update()
{
    if(this->button.getHitbox().contains({this->mouse.getPosition(*this->window).x, this->mouse.getPosition(*this->window).y}))
        this->button.howered();
    else
        this->button.unHowered();
}

void MainMenu::display()
{
    //this->window->draw(this->shape);
    this->window->draw(this->button.getDrawable());

}

MainMenu::~MainMenu()
{
}
