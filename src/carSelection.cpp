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
    float spacing = winWidth * 0.07f; 
    float buttonRadius = winWidth * 0.12f;

    int numButtons = 3;
    float totalWidth = numButtons * (2.f * buttonRadius) + (numButtons - 1) * spacing;
    
    float startX = (winWidth - totalWidth) / 2.f + buttonRadius;
    float centerY = winHeight * 0.5f;

    float arrowOffsetX = winWidth  * 0.02f;
    float arrowOffsetY = winHeight * 0.02f;
    float settingsOffsetX = winWidth  * 0.02f;
    float settingsOffsetY = winHeight * 0.02f;

    //przyciski CircleBTN
    for (int i = 0; i < numButtons; i++)
    {
        sf::Vector2f position(startX + i * (2 * buttonRadius + spacing), centerY);
        CarCircleBtn[i].setPosition(position);
        CarCircleBtn[i].setRadius(buttonRadius);
        CarCircleBtn[i].setColor(sf::Color::White);
        
        //wspolczynnik wielkosci animacji
        CarCircleBtn[i].setHoverScaleFactor(1.1f);
    }

    //wczytywanie czcionki
    font.loadFromFile("fonts/BigFont.ttf"); 

    //implementacje nazw aut pod circlebutton
    std::string names[3] = {"Auto 1", "Auto 2", "Auto 3"};
    for (int i = 0; i < numButtons; i++)
    {
        carTexts[i].setFont(font);
        carTexts[i].setString(names[i]);
        carTexts[i].setCharacterSize(30);
        carTexts[i].setFillColor(sf::Color::Black);

        // Wycentrowanie originu napisu, aby łatwiej go ustawiać
        sf::FloatRect textRect = carTexts[i].getLocalBounds();
        carTexts[i].setOrigin(textRect.width / 2.f, textRect.height / 2.f);

        // Pozycja poniżej przycisku
        float offsetY = buttonRadius + 40.f; // 40 pikseli poniżej kółka
        sf::Vector2f textPos = CarCircleBtn[i].getPosition();
        textPos.y += offsetY;
        carTexts[i].setPosition(textPos);
    }

    //pozycja strzalki
    backArrow.setPosition(sf::Vector2f(arrowOffsetX, arrowOffsetY));

    //pozycja przycisku ustawien
    settingsBtn.setPosition(sf::Vector2f(winWidth - buttonWidth - settingsOffsetX, settingsOffsetY));
}

void CarSelection::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouse->getPosition(*window));

        for (int i = 0; i < 3; i++) 
        {
            if (CarCircleBtn[i].manageHover(mouse->getPosition(*window), true)) 
            {
                CarCircleBtn[i].setHoverScaleFactor(1.3f);
            }
        }
        
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

    for (int i = 0; i < 3; i++)
    {
         // Wywołanie manageHover (bez _clicked) powoduje aktualizację stanu przycisku
         bool hovered = CarCircleBtn[i].manageHover(mousePos);
         // Jeśli przycisk nie jest pod kursorem, przywracamy domyślny współczynnik skali (tutaj 1.1f)
         if (!hovered)
         {
              CarCircleBtn[i].setHoverScaleFactor(1.1f);
         }
    }
    
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
    for(int i = 0; i < 3; i++) {

        this->window->draw(this->CarCircleBtn[i]);
        this->window->draw(carTexts[i]);
     }
}

CarSelection::~CarSelection()
{
}
