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
    const sf::Texture& getTexture(int _number) const {return playerTextures[_number];}
    const CarStats& getStats(int _number) const {return playerStats[_number];}
private:
    CarStats playerStats[3] {{300.f,7.f,5.f}, {325.f, 10.f, 5.5f}, {350.f, 11.f, 5.7f}};
    sf::Texture playerTextures[3];
};

//extern Cars cars;