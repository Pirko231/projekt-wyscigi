#include "score.h"

//sf::Font* Score::font {};

Score::Score()
{
    this->nickname.setFont(this->font);
    this->nickname.setCharacterSize(40u);
    this->bestLap.setFont(this->font);
    this->bestLap.setCharacterSize(40u);
    this->overallTime.setFont(this->font);
    this->overallTime.setCharacterSize(40u);

    this->setSize({600.f, 60.f});
    this->backround.setFillColor(sf::Color{255,128,0});
}

void Score::setContents(sf::String _nickName, sf::Time _bestLap, sf::Time _overallTime)
{
    this->nickname.setString(_nickName);
    this->bestLap.setString(std::to_string(_bestLap.asMilliseconds()));
    this->overallTime.setString(std::to_string(_overallTime.asMilliseconds()));
}

void Score::setPosition(sf::Vector2f pos)
{
    backround.setPosition(pos);
    this->nickname.setPosition(pos.x + 10.f, pos.y);
    this->bestLap.setPosition(pos.x + this->backround.getLocalBounds().width / 3.f * 2.f + 10.f, pos.y);
    this->overallTime.setPosition(pos.x + this->backround.getLocalBounds().width / 3.f + 10.f, pos.y);
}
