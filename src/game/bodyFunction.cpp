#include "bodyFunction.h"

//sf::View BodyFunction::defaultView;
//bool BodyFuncion::viewLoaded{false};

sf::Sprite BodyFunction::backgroundSprite{};
sf::Texture BodyFunction::backgroundTexture{};

BodyFunction::BodyFunction(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : functionIterator{_managingFunctionsIterator}
{
    this->window = _window;
    this->mouse = _mouse;
    this->settings = _settings;
    this->music = _music;
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
