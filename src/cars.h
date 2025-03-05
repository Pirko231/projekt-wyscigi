#pragma once

#include "raport.h"
#include "player.h"
#include "bot.h"


//'garaz' dla samochodow. wczytuje im tekstury i komunikuje sie z
//settings gdzie mozna odebrac wczytane dane
class Cars
{
public:
    Cars();
    Player player;
    void setPlayerNumber(int _number);
private:
    CarStats playerStats[3] {{100.f,10.f,5.f}, {110.f, 15.f, 5.f}, {120.f, 15.f, 7.f}};
    sf::Texture playerTextures[3];
};

//extern Cars cars;