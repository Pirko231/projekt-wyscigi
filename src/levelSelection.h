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
    //sekcja private jest calkowicie dla osoby ktora pracuje na funkcja


    // Tło ekranu
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape overlay;

   // Przyciski map (RectangleButton) oraz 
   static constexpr int MapButtonsAmount = 3;
   btn::RectangleButton mapButtons[MapButtonsAmount];
   

   //Nazwy map
   sf::Text mapNames[MapButtonsAmount];
   sf::Font font;

   //dodanie tekstur do map
   sf::Texture mapTextures[MapButtonsAmount];
   sf::Sprite mapSprites[MapButtonsAmount];

    //strzalka
    btn::SpriteButton backArrow {btn::templates.getArrowTemplate()};
    //ustawienia
    btn::SpriteButton settingsBtn {btn::templates.getSettingsTemplate()};

    int selectedMapIndex = -1;
};