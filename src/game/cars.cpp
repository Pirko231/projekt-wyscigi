#include "cars.h"

//Cars cars;

Cars::Cars()
{
    perf::Report report;
    report.open();
    report.logMessage("Cars");
    
    std::string fileNames[3] {"resources/textures/compact_blue.png", "resources/textures/sport_red.png", "resources/textures/sedan_green.png"};
    for (int i = 0; i < 3; i++)
    {
        report.addEntry("Player " + std::to_string(i), this->playerTextures[i].loadFromFile(fileNames[i]));
    }

    report.close();
}

void Cars::setPlayerNumber(int _number) const
{
    this->player.setTexture(this->playerTextures[_number], true);
    this->player.setStats(this->playerStats[_number]);
}
