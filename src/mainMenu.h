#pragma once

#include "bodyFunction.h"
#include "buttons.h"
#include <SFML/Audio.hpp>

class MainMenu : public BodyFunction    //klassa
{
public:
    MainMenu() = delete;
    MainMenu(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator);
    void handleEvents(sf::Event& _event);
    void update();
    void display();
    ~MainMenu();

    
private:
    //ta przestrzen jest calkowicie dla osoby ktora pracuje nad ta klasa
    sf::RectangleShape shape{{50.f, 50.f}};
    sf::Font font;

    //screen background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 
    sf::RectangleShape overlay;

    //buttons on the screen
    static constexpr int buttonAmount = 3;  //liczba przysiskuf
    btn::TextButton buttons[buttonAmount];  //tablica z tymi przyciskami

    //Soundtrack
    sf::Music menuMusic;
    void playMenuMusic();

};