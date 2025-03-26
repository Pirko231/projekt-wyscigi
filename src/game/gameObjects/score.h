#pragma once

#include <SFML/Graphics.hpp>

class Score : public sf::Drawable
{
public:
    Score();

    Score(sf::Font& _font) : Score()
    {this->setFont(_font);}

    sf::FloatRect getLocalBounds() const {return this->backround.getLocalBounds();}

    sf::FloatRect getGlobalBounds() const {return this->backround.getGlobalBounds();}
    
    void setContents(sf::String _nickName, sf::Time _bestLap, sf::Time _overallTime);
    
    void setPosition(sf::Vector2f pos);

    void setSize(sf::Vector2f size)
    {
        this->backround.setSize(size);
    }

    void setFont(sf::Font& _font)
    {
        this->font = _font;
        this->nickname.setFont(_font);
        this->bestLap.setFont(_font);
        this->overallTime.setFont(_font);
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(this->backround, states);
        target.draw(this->nickname, states);
        target.draw(this->bestLap, states);
        target.draw(this->overallTime, states);
    }


    sf::RectangleShape backround;

    sf::Font font;

    sf::Text nickname;

    sf::Text bestLap;

    sf::Text overallTime;
};