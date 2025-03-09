#pragma once

#include "bodyFunction.h"

class CarSelection : public BodyFunction
{
public:
    CarSelection() = delete;
    CarSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~CarSelection();

private:

// Tło ekranu
sf::Texture backgroundTexture;
sf::Sprite backgroundSprite;
sf::RectangleShape overlay;

//strzalka
btn::SpriteButton backArrow {btn::templates.getArrowTemplate()};
//ustawienia
btn::SpriteButton settingsBtn {btn::templates.getSettingsTemplate()};


//nazwy samochodow i ich atrybuty
static constexpr int NUM_CARS = 3;
static constexpr int NUM_ATTRS = 3; 

//circlebutton
btn::CircleButton CarCircleBtn[NUM_CARS];

int carAttributes[NUM_CARS][NUM_ATTRS];
btn::ProgressBar* carProgressBars[NUM_CARS][NUM_ATTRS];
std::vector<sf::RectangleShape> carInfoRects;
sf::Text carNames[NUM_CARS];
sf::Font font;

//tekstura kłódki 
sf::Texture lockTexture;
sf::Sprite lockSprite;
};