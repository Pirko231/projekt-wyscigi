#pragma once
#include "bodyFunction.h"
#include "buttons.h"
#include "raport.h"

class LevelSelection : public BodyFunction
{
public:
    LevelSelection() = delete;
    LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~LevelSelection();
private:
    //sekcja private jest calkowicie dla osoby ktora pracuje nad klasą

    sf::RectangleShape overlay;

   // przyciski map (RectBtn)
   static constexpr int MapButtonsAmount = 3;
   btn::RectangleButton mapButtons[MapButtonsAmount];
   

   //Nazwy map
   sf::Text mapNames[MapButtonsAmount];
   sf::Font font;

   //tekstury do map
   sf::Texture mapTextures[MapButtonsAmount];
   sf::Sprite mapSprites[MapButtonsAmount];

    //strzalka
    btn::SpriteButton backArrow {btn::templates.getArrowTemplate()};
    //ustawienia
    btn::SpriteButton settingsBtn {btn::templates.getSettingsTemplate()};

    int selectedMapIndex = -1;

    //tekstura kłódki 
    sf::Texture lockTexture;
    sf::Sprite lockSprite;
};