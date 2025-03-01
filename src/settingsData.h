#pragma once

//klasa przechowujaca dane ktore mozna ustawiac w ustawieniach.
//zeby ich uzyc nalezy zdobyc wskaznik od obiektu Settings.
class SettingsData
{
public:
    SettingsData() = default;
    int mainVolume {50};
    int musicVolume {50};
    int soundsVolume {50};
};