#include "levelSelection.h"

LevelSelection::LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings}
{
    
}

void LevelSelection::handleEvents(sf::Event& _event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) 
    {
        if (settings.getHitbox().contains(static_cast<sf::Vector2f>(mouse->getPosition(*window)))) 
            settings.startClickAnimation();
        
    }
}

void LevelSelection::update()
{
    
    if (settings.getHitbox().contains(static_cast<sf::Vector2f>(mouse->getPosition(*window))))
        settings.howered();
    else 
        settings.unHowered();
    

    if(this->settings.manage())
    {
        this->functionIterator = ManagingFunctionsIterator::carSelection;
        this->settings.reset();
    }
}

void LevelSelection::display()
{
    this->window->draw(this->settings);
}

LevelSelection::~LevelSelection()
{
}
