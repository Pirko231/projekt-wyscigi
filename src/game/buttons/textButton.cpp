#include "textButton.h"

btn::TextButton::TextButton(unsigned int _characterSize)
{
    //zmienne skladowe
    this->defaultCharacterSize = _characterSize;
    this->maxCharacterSize = _characterSize * 1.3;
    this->changeSizeBy = (this->maxCharacterSize - this->defaultCharacterSize) / 60;
    this->changeSizeBy += _characterSize / 15;

    //w tym momencie string ejszcze jest pusty. mozna to wywalic
    //this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});
    //this->changeSizeBy += 1;
}

btn::TextButton::TextButton(sf::Vector2f _pos, const sf::Font &_font, unsigned int _characterSize) : TextButton{_pos, _characterSize}
{
    //czcionka, reszta robiona konstrukoterm delegujacym
    this->text.setFont(_font);

    //this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});
}

btn::TextButton::TextButton(sf::Vector2f _pos, unsigned int _characterSize) : TextButton{_characterSize}
{
    //obiekty
    this->text.setPosition(_pos);
    this->text.setCharacterSize(_characterSize);
}

bool btn::TextButton::manageHover(sf::Vector2i _mousePos, bool _clicked)
{
    if (this->text.getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        if (_clicked)
            this->startClickAnimation();
        
        this->howered_();
        this->mousePos = _mousePos;
        return true;
    }
    else
        this->unHowered_();
    this->mousePos = _mousePos;

    return false;
}

bool btn::TextButton::manage()
{ 
    if (this->isAnimated_())
        this->clicked_();

    return this->isAnimationFinished_();
        
}

void btn::TextButton::setString(const sf::String &_string)
{
    this->text.setString(_string);
    //this->hitBox.setSize({static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize()), static_cast<float>(this->text.getString().getSize() * this->text.getCharacterSize())});
    //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});    
    //this->hitBox.setSize({this->text.getLocalBounds().width - this->text.getLocalBounds().left, this->text.getLocalBounds().height - this->text.getLocalBounds().top});
}

void btn::TextButton::setCharacterSize(unsigned int _characterSize, unsigned int _maxCharacterSize)
{
    this->text.setCharacterSize(_characterSize);
    this->defaultCharacterSize = _characterSize;

    if (_maxCharacterSize == 0) //samo sie ustawi gdy domniemany argument
        this->maxCharacterSize = _characterSize * 1.3;
    else
        this->maxCharacterSize = _maxCharacterSize;

    //wyliczenie predkosci zwiekszania
    this->changeSizeBy = (this->maxCharacterSize - this->defaultCharacterSize) / 60;
    this->changeSizeBy += _characterSize / 15;

    //na koniec wszystkiego ustawiamy hitbox
    //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});
}

void btn::TextButton::howered_()
{
    if (this->text.getCharacterSize() < this->maxCharacterSize)
    {
        this->text.setCharacterSize(static_cast<int>(static_cast<float>(this->text.getCharacterSize()) + this->changeSizeBy));
        //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});
    }
    else
    {
        this->text.setCharacterSize(this->maxCharacterSize);
        //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});
    }
}

void btn::TextButton::unHowered_()
{
    if (this->text.getCharacterSize() > this->defaultCharacterSize)
    {
        unsigned int previousSize {this->text.getCharacterSize()};
        this->text.setCharacterSize(static_cast<int>(static_cast<float>(this->text.getCharacterSize()) - this->changeSizeBy));
        //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});
        if (this->text.getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePos)))
            this->text.setCharacterSize(previousSize);
    }
    else
    {
        this->text.setCharacterSize(this->defaultCharacterSize);
        //this->hitBox.setSize({this->text.getLocalBounds().width, static_cast<float>(this->text.getLocalBounds().height * 1.35)});
    }
}

void btn::TextButton::clicked_()
{
    if (this->animation % this->perSecond == 0)
        if (this->text.getFillColor() == this->baseColor)
            this->text.setFillColor(this->animationColor);
        else
            this->text.setFillColor(this->baseColor);

    this->animation--;

    if (this->animation <= 0)
        this->animationFinished = true;
}
