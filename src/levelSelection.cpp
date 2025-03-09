#include "levelSelection.h"

LevelSelection::LevelSelection(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music)
    : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
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
    std::string mapTextureFiles[MapButtonsAmount] = {
        "resources/Speedway.jpeg",
        "resources/mapLevel1.jpg",
        "resources/SPEEDWAY2.0..jpg"
    };

    //wczytywanie klodki i czcionki
    lockTexture.loadFromFile("resources/Lock.png");
    lockSprite.setTexture(lockTexture);
    font.loadFromFile("fonts/BigFont.ttf");
    

    float baseRectWidth = 8.f;
    float scaledW = baseRectWidth * scaleX; 
    float desiredLockWidth = scaledW * 0.6f;
    float lockScaleFactor = desiredLockWidth / lockTexture.getSize().x;
    lockSprite.setScale(lockScaleFactor, lockScaleFactor);

    for (int i = 0; i < MapButtonsAmount; i++)
    {
        //pozycje przyciskuf
        float startX = 2.f + (i * 9.f);
        float startY = 5.f;
        float rectWidth  = 8.f;
        float rectHeight = 14.f;

        float scaledX = startX * scaleX;
        float scaledY = startY * scaleY;
        float scaledW_local = rectWidth * scaleX;
        float scaledH = rectHeight * scaleY;

        //tworzenie rectButton
        mapButtons[i] = btn::RectangleButton(
            sf::Vector2f{scaledX, scaledY},
            sf::Vector2f{scaledW_local, scaledH},
            sf::Color(150, 150, 150), 
            sf::Color(200, 200, 200)
        );

        //ustawienie nazw mapy
        mapNames[i].setFont(font);
        mapNames[i].setString(mapTitles[i]);
        mapNames[i].setCharacterSize(50);
        mapNames[i].setFillColor(sf::Color::White);
        sf::FloatRect textRect = mapNames[i].getLocalBounds();
        mapNames[i].setOrigin(textRect.width / 2.f, textRect.height / 2.f);
        sf::Vector2f textPos = mapButtons[i].getPosition();
        textPos.x += scaledW_local / 2.f;
        textPos.y += scaledH + 40.f;
        mapNames[i].setPosition(textPos);

        //wczytywanie tekstur map
        mapTextures[i].loadFromFile(mapTextureFiles[i]);
        mapSprites[i].setTexture(mapTextures[i]);

        if (mapTextures[i].getSize().x > 0 && mapTextures[i].getSize().y > 0)
        {
            float spriteMargin = 0.2f;
            float heightAdjustmentFactor = 0.75f; 
            float widthMultiplier = 1.00f;

            float scaleFactorY = (scaledH * (1 - spriteMargin) * heightAdjustmentFactor) / mapTextures[i].getSize().y;
            float scaleFactorX = (scaledW_local * widthMultiplier) / mapTextures[i].getSize().x;
            mapSprites[i].setScale(scaleFactorX, scaleFactorY);

            float spriteScaledWidth  = mapTextures[i].getSize().x * scaleFactorX;
            float spriteScaledHeight = mapTextures[i].getSize().y * scaleFactorY;

            float offsetX = (scaledW_local - spriteScaledWidth) / 2.f;
            float offsetY = (scaledH - spriteScaledHeight) / 2.f;

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
            backArrow.startClickAnimation();
        } 
        else if (settingsBtn.manageHover(mouse->getPosition(*window)))
        {
            settingsBtn.startClickAnimation();
        } 
        else 
        {
            for (int i = 0; i < MapButtonsAmount; i++) 
            {
                if (mapButtons[i].manageHover(sf::Vector2i(mouse->getPosition(*window)), true))
                {

                    bool isUnlocked = (i == 0) ? true : ((i == 1) ? settings->getData()->level2 : settings->getData()->level3);
                    if (!isUnlocked)
                    {
                        
                        continue;
                    }
                    else
                    {
                       
                        for (int i = 0; i < MapButtonsAmount; i++) 
                        {
                            if (mapButtons[i].manageHover(sf::Vector2i(mouse->getPosition(*window)), true))
                            {
                                if (isUnlocked) // Sprawdza, czy mapa jest odblokowana
                                {
                                    settings->setStartingData()->mapNumber = i;
                                    functionIterator = ManagingFunctionsIterator::carSelection;
                                    break; // Żeby nie nadpisywało się więcej razy
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void LevelSelection::update()
{
    sf::Vector2i mousePos = mouse->getPosition(*window);

    
    for (int i = 0; i < MapButtonsAmount; i++) 
    {
        mapButtons[i].manageHover(mousePos, false);
    }

   
    backArrow.manageHover(mousePos);
    settingsBtn.manageHover(mousePos);

    if (backArrow.manage())
    {
        functionIterator = ManagingFunctionsIterator::mainMenu;
        backArrow.reset();
    }
    if (settingsBtn.manage())
    {
        *this->BodyFunction::settings = !(*this->BodyFunction::settings);
        settingsBtn.reset();
    }
}

void LevelSelection::display()
{
    window->draw(backgroundSprite);
    window->draw(backArrow);
    window->draw(settingsBtn);

    
    for (int i = 0; i < MapButtonsAmount; i++) 
    {
        window->draw(mapButtons[i]);
        window->draw(mapNames[i]);
        window->draw(mapSprites[i]);

        
        if (i > 0)
        {
            bool isUnlocked = (i == 0) ? true : ((i == 1) ? settings->getData()->level2 : settings->getData()->level3);
            if (!isUnlocked)
            {
                
                sf::FloatRect btnBounds = mapButtons[i].getGlobalBounds();
                lockSprite.setPosition(
                    btnBounds.left + btnBounds.width / 2.f - lockSprite.getGlobalBounds().width / 2.f,
                    btnBounds.top + btnBounds.height / 2.f - lockSprite.getGlobalBounds().height / 2.f
                );
                window->draw(lockSprite);
            }
        }
    }
}

LevelSelection::~LevelSelection()
{
}
