#include <SFML/Graphics.hpp>

class Score : public sf::Drawable
{
public:
    Score() = default;
    
    void setPosition(sf::Vector2f pos)
    {
        backround.setPosition(pos);
    }

    void setSize(sf::Vector2f size)
    {
        this->backround.setSize(size);
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(this->backround, states);
    }

    //TODO dodac tekst zeby wyswitlaly sie wyniki

    sf::RectangleShape backround;
};