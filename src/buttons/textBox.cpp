#include "textBox.h"

btn::TextBox::TextBox(sf::Vector2f _pos, sf::Vector2f _size)
{
    this->setPosition(_pos);
    this->setSize(_size);
}

bool btn::TextBox::manageHover(sf::Vector2i _mousePos, bool _clicked)
{
    if (this->box.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        //gdyby odkomentowac te dwie linijki funkcja by dzialala tez w handleEvents
        /*if (_clicked)
            this->clicked = true;*/
        this->box.setFillColor(this->hoverColor);
    }
    else
        this->box.setFillColor(this->defaultColor);
    /*else if (_clicked)
        this->clicked = false;*/
    
    
    return false;
}

void btn::TextBox::manageClick(sf::Vector2i _mousePos, sf::Event &_event)
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

    if (_event.type == sf::Event::TextEntered)
    {
        if (_event.key.code == sf::Keyboard::Escape || _event.key.code == sf::Keyboard::Enter)
            this->clicked = false;
        else
            this->textString += _event.text.unicode;
    }
}

void btn::TextBox::setPosition(sf::Vector2f _pos)
{
    this->box.setPosition(_pos);

    this->text.setPosition({this->box.getGlobalBounds().left + this->text.getLocalBounds().width / 3.f, this->box.getGlobalBounds().width - this->text.getLocalBounds().height * 2.f});
}

void btn::TextBox::setFillColor(sf::Color _defaultColor, sf::Color _hoverColor, sf::Color _fontColor, sf::Color _cursorColor, sf::Color _outlineFillColor)
{
    this->defaultColor = _defaultColor;
    this->hoverColor = _hoverColor;
    this->text.setFillColor(_fontColor);
    this->cursor.setFillColor(_cursorColor);
    this->box.setOutlineColor(_outlineFillColor);
}
