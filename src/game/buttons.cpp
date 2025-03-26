#include "buttons.h"

btn::Templates::Templates()
{
    Raport raport;
    raport.open();

    raport.logMessage("Template textures");
    
    raport.addEntry("Settings icon", this->settingTemplatetxt.loadFromFile("resources/textures/settingsIcon.png"));

    raport.addEntry("Arrow icon", this->arrowTemplatetxt.loadFromFile("resources/textures/arrow.png"));

    raport.addEntry("X icon unhovered", this->xTemplateUnHoweredtxt.loadFromFile("resources/textures/xButton.png"));
    
    raport.addEntry("X icon hovered", this->xTemplateHoweredtxt.loadFromFile("resources/textures/xButtonHowered.png"));
    
    raport.close();

    //dopiero po zamknieciu raportu przypisujemy tekstury
    this->settingsTemplate.setTexture(this->settingTemplatetxt);
    this->settingsTemplate.setScale({0.18f, 0.18f});

    this->arrowTemplate.setTexture(this->arrowTemplatetxt);
    this->arrowTemplate.setScale({0.2f,0.2f});

    this->xTemplate.setTextures(this->xTemplateHoweredtxt, this->xTemplateUnHoweredtxt);
    this->xTemplate.setScale({0.4f, 0.4f});
}

const btn::Templates btn::templates;


