#include "buttons.h"

btn::TemplateTexturesSpriteButton::TemplateTexturesSpriteButton()
{
    Raport raport;
    raport.open();

    raport.logMessage("Template textures");
    raport.addEntry("Settings icon", this->settingTemplatetxt.loadFromFile("resources/settingsIcon.png"));

    raport.close();
        
}


const btn::TemplateTexturesSpriteButton btn::templateData;

const btn::SpriteButton btn::settingsTemplate{{0.f, 0.f}, templateData.settingTemplatetxt, {1.f, 1.f}};


