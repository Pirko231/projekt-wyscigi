#include "bot.h"

Bot::Bot() : Car{}
{
}

void Bot::handleEvents(sf::Event &ev)
{
    //zeby nie bylo ostrzezenia unusedVariable
    int i{0};
    if (ev.type == sf::Event::Closed)
        i++;
}
