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
    mutable Player player;
    void setPlayerNumber(int _number) const;
private:
    CarStats playerStats[3] {{300.f,10.f,5.f}, {350.f, 20.f, 5.f}, {370.f, 55.f, 10.f}};
    sf::Texture playerTextures[3];
};

//extern Cars cars;