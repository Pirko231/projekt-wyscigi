#include "textButton.h"

btn::TextButton::TextButton(sf::Vector2f _pos, const sf::Font &_font, unsigned int _characterSize) : TextButton{_pos, _characterSize}
{
    //czcionka, reszta robiona konstrukoterm delegujacym
    this->text.setFont(_font);

    this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});
}

btn::TextButton::TextButton(sf::Vector2f _pos, unsigned int _characterSize)
{
    //zmienne skladowe
    this->defaultCharacterSize = _characterSize;
    this->maxCharacterSize = _characterSize * 1.3;
    this->changeSizeBy = (this->maxCharacterSize - this->defaultCharacterSize) / 60; 

    
    //obiekty
    this->text.setPosition(_pos);
    this->text.setCharacterSize(_characterSize);
    
    this->hitBox.setPosition(_pos);
    this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});
}

void btn::TextButton::clicked()
{
}

void btn::TextButton::howered()
{
    if (this->text.getCharacterSize() < this->maxCharacterSize)
        this->text.setCharacterSize(static_cast<int>(static_cast<float>(this->text.getCharacterSize()) + this->changeSizeBy));
    else
        this->text.setCharacterSize(this->maxCharacterSize);
}

void btn::TextButton::unHowered()
{
    if (this->text.getCharacterSize() > this->defaultCharacterSize)
        this->text.setCharacterSize(static_cast<int>(static_cast<float>(this->text.getCharacterSize()) - this->changeSizeBy));
    else
        this->text.setCharacterSize(this->defaultCharacterSize);
}
