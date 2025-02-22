#pragma once
#include "buttons/textButton.h"
#include "buttons/spriteButton.h"
#include "raport.h"

//w tym pliku zebrane beda wszystkie przyciski z folderu button.
//wystarczy includowac tylko ten plik aby miec do nich dostep

namespace btn
{

    // struktura wczytujaca dane do template definiowana w buttons.h
    struct TemplateTexturesSpriteButton
    {
        TemplateTexturesSpriteButton();
        
        sf::Texture settingTemplatetxt;
    };

    // tutaj wczytywane są tekstury. Nie nalezy tego uzywac
    const extern TemplateTexturesSpriteButton templateData;

    // template do ikony ustawien. Nalezy skopiowac to do innego obiektu typu btn::SpriteButton
    const extern btn::SpriteButton settingsTemplate;
};