#include "levelSelection.h"

LevelSelection::LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    //screen background
    backgroundTexture.loadFromFile("resources/mainMenuBackground.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(_window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(_window->getSize().y) / backgroundTexture.getSize().y
    );


    float scaleX = static_cast<float>(_window->getSize().x) / 30.f;
    float scaleY = static_cast<float>(_window->getSize().y) / 22.f;

    


    std::string mapTitles[MapButtonsAmount] = {"Speedway", "Desert", "Jungle"};

    // pozycje i rozmiar przyciskuf
    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.25f;
    float buttonHeight = winHeight * 0.15f;
    float spacing = winWidth * 0.02f;
    float startX = (winWidth - (MapButtonsAmount * buttonWidth + (MapButtonsAmount - 1) * spacing)) / 2.0f;
    float startY = winHeight * 0.4f; 

    for (int i = 0; i < MapButtonsAmount; i++)
    {
       
        float startX = 2.f + (i * 9.f);
        float startY = 5.f;   
        float rectWidth = 8.f;
        float rectHeight = 14.f;

        
        float scaledX = startX * scaleX;
        float scaledY = startY * scaleY;
        float scaledW = rectWidth * scaleX;
        float scaledH = rectHeight * scaleY;

        
        mapButtons[i] = btn::RectangleButton(
            sf::Vector2f{scaledX, scaledY},
            sf::Vector2f{scaledW, scaledH},
            sf::Color(150, 150, 150),   //szary
            sf::Color(200, 200, 200)    //jasnoszary
        );

        //tekst do nazw map
        mapNames[i].setFont(font);
        mapNames[i].setString(mapTitles[i]);
        mapNames[i].setCharacterSize(static_cast<unsigned int>(24 * scaleY)); 
        mapNames[i].setFillColor(sf::Color::White);

        // wysrodkowanie tekstu map nad przyciski
        sf::FloatRect textRect = mapNames[i].getLocalBounds();
         float textWidth = textRect.width;
         float textHeight = textRect.height;
         float textOffsetY = 1.f * scaleY;
         float posX = scaledX + (scaledW / 2.f) - (textWidth / 2.f);
         float posY = scaledY - textHeight - textOffsetY;
         mapNames[i].setPosition(posX, posY);
    

         backArrow.setPosition(sf::Vector2f{20.f, 15.f});
    
    settingsBtn.setPosition(
         sf::Vector2f(
             static_cast<float>(winWidth) - 20.f - settingsBtn.getGlobalBounds().width - 20.f,
             20.f
         )
    );
    }
    

}

void LevelSelection::handleEvents(sf::Event& _event)
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
        else 
        {
            for (int i = 0; i < MapButtonsAmount; i++) 
            if (mapButtons[i].manageHover(sf::Vector2i(mouse->getPosition(*window)), true))
                {
                      
                    this->settings->setStartingData()->mapNumber = i;    
                    functionIterator = ManagingFunctionsIterator::carSelection;
                    break;
                }
                    
        }
    }
}

void LevelSelection::update()
{
    sf::Vector2i mousePos = (mouse->getPosition(*window));

    //Hover dla mapButtons
    for (int i = 0; i < MapButtonsAmount; i++) 
    {
        mapButtons[i].manageHover((mousePos), false);
    }

    //Hover dla strzałki
    backArrow.manageHover(mousePos);
        

    //hover dla ustawień
    settingsBtn.manageHover(mousePos);

    if (this->backArrow.manage())
    {
        //this->settings->setStartingData()->mapNumber 
        functionIterator = ManagingFunctionsIterator::mainMenu;
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

void LevelSelection::display()
{
    window->draw(backgroundSprite);
    this->window->draw(this->backArrow);
    this->window->draw(this->settingsBtn);

    // Rysujemy przyciski map oraz ich etykiety
    for (int i = 0; i < MapButtonsAmount; i++) 
    {
        window->draw(mapButtons[i]);
        window->draw(mapNames[i]);
    }
}

LevelSelection::~LevelSelection()
{
}
