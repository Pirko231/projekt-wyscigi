#include "bodyFunction.h"

sf::Sprite BodyFunction::backgroundSprite{};
sf::Texture BodyFunction::backgroundTexture{};

BodyFunction::BodyFunction(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : functionIterator{_managingFunctionsIterator}
{
    this->window = _window;
    this->mouse = _mouse;
    this->settings = _settings;
}

void BodyFunction::initBackground()
{
    perf::Raport raport;
    raport.open();
    raport.logMessage("Background");
    raport.addEntry("Wczytywanie tla ekranu", BodyFunction::backgroundTexture.loadFromFile("resources/textures/mainMenuBackground.jpg"));
    raport.close();
    BodyFunction::backgroundSprite.setTexture(BodyFunction::backgroundTexture);
}

BodyFunction::~BodyFunction()
{

}
