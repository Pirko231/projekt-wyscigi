#include "settings.h"

Settings::Settings(sf::RenderWindow* _window, sf::Mouse* _mouse)
{
    this->mouse = _mouse;
    this->window = _window;

    Raport raport;
    raport.open();
    raport.logMessage("Settings");

    raport.addEntry("Wczytywanie czcionki", this->font.loadFromFile("fonts/BigFont.ttf"));

    raport.close();

    this->textBox.setFillColor(sf::Color::Black);
    this->textBox.setFont(this->font);
    
    this->background.setFillColor(sf::Color{81, 81, 81});
    this->background.setSize({static_cast<float>(this->window->getSize().x / 2.5), static_cast<float>(this->window->getSize().x / 2.1)});
    this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1.1)};
    this->background.setPosition(this->startPos);
    
    this->texts[0].first.setString("USTAWIENIA"); 
    this->texts[0].first.setFont(this->font); 
    this->texts[0].first.setCharacterSize(50); 
    this->texts[0].first.setFillColor(sf::Color{255, 255, 255});
    
    this->mainVolume.setSize({400.f, 10.f}); 
    this->texts[1].first.setString("Glowna Glosnosc"); 
    this->texts[1].first.setFont(this->font);
    
    this->musicVolume.setSize({400.f, 10.f}); 
    this->texts[2].first.setString("Glosnosc muzyki"); 
    this->texts[2].first.setFont(this->font);
    
    this->soundsVolume.setSize({400.f, 10.f}); 
    this->texts[3].first.setString("Glosnosc dzwiekow"); 
    this->texts[3].first.setFont(this->font);

    // Ustawienie czcionki dla liczników w suwakach
    this->mainVolume.setCounterFont(this->font);
    this->musicVolume.setCounterFont(this->font);
    this->soundsVolume.setCounterFont(this->font);

    // Przypisanie przycisków oraz ich przesunięć
    this->buttons[0] = {&this->x, {this->background.getLocalBounds().width - this->x.getLocalBounds().width / 5, -(this->x.getLocalBounds().height / 5)}};
    this->buttons[1] = {&this->mainVolume, {this->background.getLocalBounds().width - static_cast<int>(this->mainVolume.getLocalBounds().width * 1.15), this->background.getLocalBounds().top + this->mainVolume.getLocalBounds().height * 9}};
    this->buttons[2] = {&this->musicVolume, {this->background.getLocalBounds().width - static_cast<int>(this->musicVolume.getLocalBounds().width * 1.15), this->background.getLocalBounds().top + this->musicVolume.getLocalBounds().height * 9 + this->musicVolume.getLocalBounds().height * 6}};
    this->buttons[3] = {&this->soundsVolume, {this->background.getLocalBounds().width - static_cast<int>(this->soundsVolume.getLocalBounds().width * 1.15), this->background.getLocalBounds().top + this->soundsVolume.getLocalBounds().height * 9 + this->soundsVolume.getLocalBounds().height * 12}};

    this->texts[0].second = {this->texts[0].first.getLocalBounds().width / 1.3f, -(this->texts[0].first.getLocalBounds().height / 1.5f)};
    
    // Ustawienie pozycji tekstów względem przycisków (od indeksu 1, gdyż 0 to nagłówek)
    for (int i = 1; i < this->textsAmount; i++)
    {
        this->texts[i].second = {this->buttons[i].second.x, this->buttons[i].second.y - this->buttons[i].first->getLocalBounds().height - this->texts[i].first.getLocalBounds().height * 1.5f};
    }
}



void Settings::handleEvents(sf::Event &_event)
{
    this->textBox.manageClick(this->mouse->getPosition(*this->window), _event);
    if (_event.type == sf::Event::MouseButtonPressed)
    {
        if (_event.mouseButton.button == sf::Mouse::Left)
        {
            if (this->x.manageHover(this->mouse->getPosition(*this->window), true))
                *this = false;
            
        }
        
    }
    if (_event.type == sf::Event::MouseButtonPressed || _event.type == sf::Event::MouseMoved)
    {
        this->mainVolume.manageHover(this->mouse->getPosition(*this->window), this->mouse->isButtonPressed(sf::Mouse::Left));
        this->musicVolume.manageHover(this->mouse->getPosition(*this->window), this->mouse->isButtonPressed(sf::Mouse::Left));
        this->soundsVolume.manageHover(this->mouse->getPosition(*this->window), this->mouse->isButtonPressed(sf::Mouse::Left));
    }
}

void Settings::update()
{
    this->x.manageHover(this->mouse->getPosition(*this->window));
    this->textBox.manageHover(this->mouse->getPosition(*this->window));
    //this->mainVolume.manageHover(this->mouse->getPosition(*this->window));
    this->mainVolume.updateValue();
    this->musicVolume.updateValue();
    this->soundsVolume.updateValue();

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
    for (int i = 0; i < this->buttonAmount; i++)
        this->window->draw(*this->buttons[i].first);
    
    for (int i = 0; i < this->textsAmount; i++)
        this->window->draw(this->texts[i].first);
    this->window->draw(this->textBox);
    /*this->window->draw(this->x);
    this->window->draw(this->mainVolume);*/
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
        this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1.1)};
        //this->startPos = this->background.getPosition();
        //this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y)};
        this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 8)};
    
        if (this->animation)
            this->startPos = this->background.getPosition();
        
        this->background.setPosition(this->startPos);
        for (int i = 0; i < this->buttonAmount; i++)
        {
            //this->buttons[i].second = {this->startPos.x + this->background.getLocalBounds().width - this->buttons[i].first->getLocalBounds().width / 5, this->startPos.y - this->buttons[i].first->getLocalBounds().height / 5};
        }
    }
    else
    {
        this->quitting = true;
        this->startPos = this->background.getPosition();
        //this->startPos = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 2)};
        this->destination = {static_cast<float>(this->window->getSize().x / 2) - this->background.getLocalBounds().width / 2.f, static_cast<float>(this->window->getSize().y / 1)};


        for (int i = 0; i < this->buttonAmount; i++)
        {
            //this->buttons[i].second.y = this->buttons[i].first->getPosition().y;
        }
    }
    
    //this->isTurnedOn = _isOn;
    this->animation.startAnimation(this->startPos, this->destination);
}

Settings::~Settings()
{
}

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
            _settings.buttons[i].first->setPosition(_settings.background.getPosition() + _settings.buttons[i].second);
        for (int i = 0; i < _settings.textsAmount; i++)
            _settings.texts[i].first.setPosition(_settings.background.getPosition() + _settings.texts[i].second);        

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

    for (int i = 0; i < _settings.textsAmount; i++)
        _settings.texts[i].first.move(this->moveBy);
    
    for (int i = 0; i < _settings.buttonAmount; i++)
        _settings.buttons[i].first->move(this->moveBy);
    
    
    _settings.background.move(this->moveBy);

    if (_settings.quitting && this->animation <= 0)
    {
        //_settings.isTurnedOn = false;
        this->animation = this->maxAnimation;
        
    }
}

void Settings::AnimationUp::reset()
{
    this->animation = this->maxAnimation;
}
