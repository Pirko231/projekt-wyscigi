#include "score.h"

Score::Score()
{
    this->nickname.setFont(this->font);
    this->bestLap.setFont(this->font);
    this->overallTime.setFont(this->font);

    this->backround.setSize({200.f, 50.f});
    this->backround.setFillColor(sf::Color::Yellow);
}
