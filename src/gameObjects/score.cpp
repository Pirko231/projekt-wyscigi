#include "score.h"

Score::Score()
{
    this->nickname.setFont(this->font);
    this->bestLap.setFont(this->font);
    this->overallTime.setFont(this->font);

    this->setSize({600.f, 60.f});
    this->backround.setFillColor(sf::Color{255,128,0});
}
