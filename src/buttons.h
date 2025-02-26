#pragma once
#include "buttons/textButton.h"
#include "buttons/spriteButton.h"
#include "buttons/howeredSpriteButton.h"
#include "buttons/RectangleButton.h"
#include "raport.h"

//w tym pliku zebrane beda wszystkie przyciski z folderu button.
//wystarczy includowac tylko ten plik aby miec do nich dostep

namespace btn
{

    // struktura wczytujaca dane do template definiowana w buttons.h
    class Templates
    {
    public:
        //tworzy obiekt. NIE UZYWAC TEGO TYLKO OBIEKTU 'templates' zadeklarowanego w 'buttons.h'
        Templates();

        // template do ikony ustawien. Nalezy skopiowac to do innego obiektu typu btn::SpriteButton
        const btn::SpriteButton& getSettingsTemplate() const {return this->settingsTemplate;}

        //template do strzalki. Nalezy skopiowac to do innego obiektu typu btn::SpriteButton
        const btn::SpriteButton& getArrowTemplate() const {return this->arrowTemplate;}

        //template do x (takiego co wychodzi z czegos, jak np. ten sluzacy do zamykania okna)
        //Nalezy skopiowac to do innego obiektu typu btn::SpriteButton
        const btn::HoweredSpriteButton& getXTemplate() const {return this->xTemplate;}
    private:

        sf::Texture settingTemplatetxt;
        btn::SpriteButton settingsTemplate;

        sf::Texture arrowTemplatetxt;
        btn::SpriteButton arrowTemplate;

        sf::Texture xTemplateHoweredtxt;
        sf::Texture xTemplateUnHoweredtxt;
        btn::HoweredSpriteButton xTemplate;
    };

    //tutaj są przechowywane templates. jesli chcesz skopiowac template
    //to nalezy uzyc tego obiektu.
    const extern btn::Templates templates;
};