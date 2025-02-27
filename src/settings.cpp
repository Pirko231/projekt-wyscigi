#include "settings.h"

Settings::Settings(sf::RenderWindow* _window, sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->window = _window;
    this->data = new SettingsData;

    

    Raport raport;
    raport.open();


    raport.close();
    
    
    this->background.setFillColor(sf::Color{117, 117, 117});
    this->background.setSize({static_cast<float>(this->window->getSize().x / 2.5), static_cast<float>(this->window->getSize().x / 2.2)});
    this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, this->window->getSize().y / 2};
    this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)};
    this->background.setPosition(this->startPos);
    //this->background.setPosition({static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)});
    
    //wszystko musi byc zalezne od startPos i destination

    this->x.setPosition({this->background.getPosition().x + this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, this->background.getPosition().y - this->x.getLocalBounds().height / 5});

    //przypisanie adresow do tablicy
    this->buttons[0] = {&this->x,{this->background.getPosition().x + this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, this->background.getPosition().y - this->x.getLocalBounds().height / 5}}; 
}

void Settings::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed)
        if (_event.mouseButton.button == sf::Mouse::Left)
            if (this->x.manageHover(this->mouse->getPosition(*this->window), true))
                this->isTurnedOn = false;
}

void Settings::update()
{
    this->x.manageHover(this->mouse->getPosition(*this->window));

    if (this->animation)
        this->animation(*this);
}

void Settings::display()
{
    this->window->draw(this->background);
    this->window->draw(this->x);
}

void Settings::operator=(bool _isOn)
{
    this->isTurnedOn = _isOn;
    this->animation.startAnimation(this->startPos, this->destination);
}

Settings::~Settings()
{
    delete this->data;
}

/*void Settings::animationUp::()
{
}*/

void Settings::AnimationUp::startAnimation(sf::Vector2f _currentPos, sf::Vector2f _destination)
{
    this->currentPos = _currentPos;
    this->destination = _destination;

    this->animation--; 
    this->destination = _destination;
    this->currentPos = _currentPos;
    this->moveBy = {/*(this->currentPos.x - this->destination.y) / this->framerate*/0.f, (this->destination.y - this->currentPos.y) / this->framerate * this->speed};

    this->animationStarted = true;
}

void Settings::AnimationUp::operator()(Settings &_settings)
{
    //tutaj dokonujemy zalozenia ze animacja sie juz zaczela
    
    if (this->animationStarted)
    {
        //tutaj trzeba ustawic pozycje wszystkich obiektow na 'start'
        _settings.background.setPosition(this->currentPos);

        for (int i = 0; i < _settings.buttonAmount; i++)
        {
            _settings.buttons[i].first->setPosition(_settings.buttons[i].second);
        }

        this->animationStarted = false;
    }
    
    if (_settings.background.getPosition().y <= this->destination.y)
    {
        this->animationStarted = false;
        this->animation = this->maxAnimation;
    }

    for (int i = 0; i < _settings.buttonAmount; i++)
    {
        _settings.buttons[i].first->move(this->moveBy);
    }
    
    _settings.background.move(this->moveBy);
}
