#include "textBox.h"

TextBox::TextBox(sf::Vector2f _pos, sf::Vector2f _size)
{
    this->setPosition(_pos);
    this->setSize(_size);
}

bool TextBox::manageHover(sf::Vector2i _mousePos, bool _clicked)
{
    if (this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        //gdyby odkomentowac te dwie linijki funkcja by dzialala tez w handleEvents
        /*if (_clicked)
            this->clicked = true;*/

        
    }
    /*else if (_clicked)
        this->clicked = false;*/
    
    return false;
}

void TextBox::manageClick(sf::Vector2i _mousePos, sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
            if (this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
                this->clicked = true;
            else 
                this->clicked = false;
    }
    
    if (!this->clicked)
        return;

    if (_event.type == sf::Event::KeyPressed)
    {
        if (_event.key.code == sf::Keyboard::Escape || _event.key.code == sf::Keyboard::Enter)
            this->clicked = false;
        else
            this->textString += _event.text.unicode;
    }
}
