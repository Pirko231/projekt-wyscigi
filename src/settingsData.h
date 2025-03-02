#pragma once

#include <fstream>
#include "player.h"

//po tym jak wybierze sie level i car tutaj zapisane będą wybory
//aby sie do nich dostac nalezy uzyc funkcji w settings
struct StartLevel
{
    Player* player{nullptr};
    int mapNumber{-1};
};

//klasa przechowujaca dane ktore mozna ustawiac w ustawieniach.
//zeby ich uzyc nalezy zdobyc wskaznik od obiektu Settings.
class SettingsData
{
public:
    friend class Settings;
    //otwiera plik i wczytuje dane
    SettingsData();
    //otwiera plik i zapisuje dane
    ~SettingsData();
    int mainVolume {50};
    int musicVolume {50};
    int soundsVolume {50};

    bool level1 {true};
    bool level2 {false};
    bool level3 {false};

    bool car1 {true};
    bool car2 {false};
    bool car3 {false};
private:
    //friend const StartLevel* Settings::getStartingData() const;
    //przechowuje dane o tym jaki level i car zostal wybrany
    StartLevel startLevel;
};

