#include "settings.h"

Settings::Settings(sf::RenderWindow* _window, sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->window = _window;

    Raport raport;
    raport.open();


    raport.close();
    
    
    this->background.setFillColor(sf::Color{117, 117, 117});
    this->background.setSize({static_cast<float>(this->window->getSize().x / 2.5), static_cast<float>(this->window->getSize().x / 2.2)});
    this->background.setPosition({static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)});
    
    this->x.setPosition({this->background.getPosition().x + this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, this->background.getPosition().y - this->x.getLocalBounds().height / 5});
}

void Settings::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed)
        if (_event.mouseButton.button == sf::Mouse::Left)
            if (this->x.manageHover(this->mouse->getPosition(*this->window), true))
                this->isTurnedOn = false;
}

void Settings::update()
{
    this->x.manageHover(this->mouse->getPosition(*this->window));
}

void Settings::display()
{
    this->window->draw(this->background);
    this->window->draw(this->x);
}
