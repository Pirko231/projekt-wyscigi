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

    //tekstury map
    std::string mapTextureFiles[MapButtonsAmount] = {
        "resources/Speedway.jpeg",
        "resources/mapLevel1.jpg",
        "resources/SPEEDWAY2.0..jpg"
    };
    //wczytywanie czcionki
    font.loadFromFile("fonts/BigFont.ttf");

    for (int i = 0; i < MapButtonsAmount; i++)
    {
        // pozycje do kazdego przycisku
        float startX = 2.f + (i * 9.f);
        float startY = 5.f;
        float rectWidth  = 8.f;
        float rectHeight = 14.f;

        float scaledX = startX * scaleX;
        float scaledY = startY * scaleY;
        float scaledW = rectWidth  * scaleX;
        float scaledH = rectHeight * scaleY;

        //inicjalizacja rectangleBtn
        mapButtons[i] = btn::RectangleButton(
            sf::Vector2f{scaledX, scaledY},
            sf::Vector2f{scaledW, scaledH},
            sf::Color(150, 150, 150), 
            sf::Color(200, 200, 200)  
        );

        //pozycja i cechy tekstu
        mapNames[i].setFont(font);
        mapNames[i].setString(mapTitles[i]);
        mapNames[i].setCharacterSize(50);
        mapNames[i].setFillColor(sf::Color::White);

        //wysrodkowanie napisow
        sf::FloatRect textRect = mapNames[i].getLocalBounds();
        mapNames[i].setOrigin(textRect.width / 2.f, textRect.height / 2.f);

        sf::Vector2f textPos = mapButtons[i].getPosition();
        textPos.x += scaledW / 2.f;   
        textPos.y += scaledH + 40.f; 
        mapNames[i].setPosition(textPos);

        mapTextures[i].loadFromFile(mapTextureFiles[i]);
        mapSprites[i].setTexture(mapTextures[i]);

        if (mapTextures[i].getSize().x > 0 && mapTextures[i].getSize().y > 0)
        {
            float spriteMargin = 0.2f;  // margines w osi Y
            float heightAdjustmentFactor = 0.75f; 
            float widthMultiplier = 1.00f; 

            float scaleFactorY = (scaledH * (1 - spriteMargin) * heightAdjustmentFactor) / mapTextures[i].getSize().y;
            float scaleFactorX = (scaledW * widthMultiplier) / mapTextures[i].getSize().x;
            mapSprites[i].setScale(scaleFactorX, scaleFactorY);

            float spriteScaledWidth  = mapTextures[i].getSize().x * scaleFactorX;
            float spriteScaledHeight = mapTextures[i].getSize().y * scaleFactorY;

            float offsetX = (scaledW - spriteScaledWidth)   / 2.f;
            float offsetY = (scaledH - spriteScaledHeight)  / 2.f;

            mapSprites[i].setPosition(
                mapButtons[i].getPosition().x + offsetX,
                mapButtons[i].getPosition().y + offsetY
            );
        }
    }
    backArrow.setPosition(sf::Vector2f{20.f, 15.f});
    settingsBtn.setPosition(sf::Vector2f(
        static_cast<float>(_window->getSize().x) - 20.f - settingsBtn.getGlobalBounds().width - 20.f, 
        20.f
    ));
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
        window->draw(mapSprites[i]);
    }
}

LevelSelection::~LevelSelection()
{
}
