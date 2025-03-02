#include "carSelection.h"

CarSelection::CarSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    //screen background
    backgroundTexture.loadFromFile("resources/mainMenuBackground.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(_window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(_window->getSize().y) / backgroundTexture.getSize().y
    );

    //koordynaty do ustalania miejsc przyciskow
    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.09f;
    float buttonHeight = winHeight * 0.15f;
    float spacing = winWidth * 0.02f; 

    //ustawienie backArrowBtn
    backArrow.setPosition(sf::Vector2f(spacing, spacing));

    //ustawienia settingsbutton
    settingsBtn.setPosition(sf::Vector2f(winWidth - buttonWidth - spacing, spacing));
   
    


}

void CarSelection::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouse->getPosition(*window));

        
        if (backArrow.manageHover(mouse->getPosition(*window)))
        {
            this->backArrow.startClickAnimation();
        } 
        else if (settingsBtn.manageHover(mouse->getPosition(*window)))
        {
            settingsBtn.startClickAnimation();
        } 



    }
}

void CarSelection::update()
{
    sf::Vector2i mousePos = (mouse->getPosition(*window));

    //Hover dla strzałki
    backArrow.manageHover(mousePos);

    //hover dla ustawień
    settingsBtn.manageHover(mousePos);

    if (this->backArrow.manage())
    {
        //this->settings->setStartingData()->mapNumber 
        functionIterator = ManagingFunctionsIterator::levelSelection;
        this->backArrow.reset();
    }
    if (this->settingsBtn.manage())
    {
        if (*this->BodyFunction::settings)
            *this->BodyFunction::settings = false;
        else
            *this->BodyFunction::settings = true;
        this->settingsBtn.reset();

    }
    
}



void CarSelection::display()
{
    window->draw(backgroundSprite);
    this->window->draw(this->backArrow);
    this->window->draw(this->settingsBtn);
}

CarSelection::~CarSelection()
{
}
