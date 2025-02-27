#include "settings.h"

Settings::Settings(sf::RenderWindow* _window, sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->window = _window;
    this->data = new SettingsData;

    Raport raport;
    raport.open();


    raport.close();
    
    this->background.setFillColor(sf::Color{81, 81, 81});
    this->background.setSize({static_cast<float>(this->window->getSize().x / 2.5), static_cast<float>(this->window->getSize().x / 2.2)});
    this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1.2)};
    //this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)};
    this->background.setPosition(this->startPos);
    //this->background.setPosition({static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)});
    
    //wszystko musi byc zalezne od startPos i destination

    //this->x.setPosition({this->background.getPosition().x + this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, this->background.getPosition().y - this->x.getLocalBounds().height / 5});

    //przypisanie adresow do tablicy
    this->buttons[0] = {&this->x,{this->background.getPosition().x + this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, this->background.getPosition().y - this->x.getLocalBounds().height / 5}}; 
}

void Settings::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed)
        if (_event.mouseButton.button == sf::Mouse::Left)
            if (this->x.manageHover(this->mouse->getPosition(*this->window), true))
                *this = false;
}

void Settings::update()
{
    this->x.manageHover(this->mouse->getPosition(*this->window));

    if (this->animation)
        this->animation(*this);
    else if (this->quitting)
    {
        *this = false;
        this->animation.reset();
    }
}

void Settings::display()
{
    this->window->draw(this->background);
    this->window->draw(this->x);
}

void Settings::operator=(bool _isOn)
{
    if (this->quitting)
    {
        if (!this->animation)
        {
            this->isTurnedOn = false;
            this->quitting = false;
            return;
        }
    }
    
    if (_isOn)
        this->lastTurnedOn = true;
    else
        this->lastTurnedOn = !this->lastTurnedOn;
        /*if (!this->animation)
            this->lastTurnedOn = false;
        else
            this->lastTurnedOn = true;*/

    if (this->lastTurnedOn) //_isOn
    {
        this->isTurnedOn = true;
        this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1.2)};
        //this->startPos = this->background.getPosition();
        //this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y)};
        this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)};
    
        if (this->animation)
            this->startPos = this->background.getPosition();
        
        this->background.setPosition(this->startPos);
        for (int i = 0; i < this->buttonAmount; i++)
        {
            this->buttons[i].second = {this->startPos.x + this->background.getLocalBounds().width - this->buttons[i].first->getLocalBounds().width / 5, this->startPos.y - this->buttons[i].first->getLocalBounds().height / 5};
        }
    }
    else
    {
        this->quitting = true;
        this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 2)};
        this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1)};


        for (int i = 0; i < this->buttonAmount; i++)
        {
            this->buttons[i].second.y = this->buttons[i].first->getPosition().y;
        }
    }
    
    //this->isTurnedOn = _isOn;
    this->animation.startAnimation(this->background.getPosition(), this->destination);
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
    this->moveBy = {0.f, (this->destination.y - this->currentPos.y) / this->framerate * this->speed};

    this->animationStarted = true;
}

void Settings::AnimationUp::operator()(Settings& _settings)
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
    
    if (!_settings.quitting)
    {
        if (_settings.background.getPosition().y <= this->destination.y)
        {
            //this->animationStarted = false;
            this->animation = this->maxAnimation;
        }
    }
    else
    {
        if (this->moveBy.y < 0)
        {
            _settings.quitting = false;
            //this->moveBy = {this->moveBy.x * - 1, this->moveBy.y * - 1};
            //_settings.lastTurnedOn = !_settings.lastTurnedOn;
        }
        else if (_settings.background.getPosition().y >= this->destination.y)
        {
            //this->animationStarted = false;
            this->animation = this->maxAnimation;
        }
    }

    for (int i = 0; i < _settings.buttonAmount; i++)
    {
        _settings.buttons[i].first->move(this->moveBy);
    }
    
    _settings.background.move(this->moveBy);

    if (_settings.quitting && this->animation <= 0 )
    {
        //_settings.isTurnedOn = false;
        this->animation = this->maxAnimation;
        
    }
}

void Settings::AnimationUp::reset()
{
    this->animation = this->maxAnimation;
}
