#include "settingsData.h"

SettingsData::SettingsData()
{
    std::fstream file;
    file.open("unlocks.txt", std::ios::in);
    if (file.is_open())
    {
        //pomijamy wgrywanie level1 i car1 bo zawsze są dostepne
        file >> this->level2;
        file >> this->level3;

        file >> this->car2;
        file >> this->car3;
    }
}

SettingsData::~SettingsData()
{
    std::fstream file;
    file.open("unlocks.txt", std::ios::out);
    if (file.is_open())
    {
        //pomijamy zapisywanie level1 i car1 bo zawsze są dostepne
        file << this->level2 << '\n';
        file << this->level3 << '\n';

        file << this->car2 << '\n';
        file << this->car3 << '\n';
    }
}
