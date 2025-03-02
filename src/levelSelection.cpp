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

    // pozycje i rozmiar przyciskuf
    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.25f;
    float buttonHeight = winHeight * 0.15f;
    float spacing = winWidth * 0.02f;
    float startX = (winWidth - (MapButtonsAmount * buttonWidth + (MapButtonsAmount - 1) * spacing)) / 2.0f;
    float startY = winHeight * 0.4f; 

    for (int i = 0; i < MapButtonsAmount; i++) 
    {
        sf::Vector2f pos(startX + i * (buttonWidth + spacing), startY);
        sf::Vector2f size(buttonWidth, buttonHeight * 3.f);
        
        sf::Color baseColor = sf::Color(150, 150, 150);
        sf::Color hoverColor = sf::Color(200, 200, 200);

        mapButtons[i] = btn::RectangleButton(pos, size, baseColor, hoverColor);

        
        mapNames[i].setFont(font);
        mapNames[i].setString("Mapa " + std::to_string(i + 1));
        mapNames[i].setCharacterSize(static_cast<unsigned int>(buttonHeight * 0.3f));
        mapNames[i].setFillColor(sf::Color::White);

        mapNames[i].setPosition(pos.x + size.x / 2.0f - 20.f, pos.y - 30.f); 
    
        
    }
    //backArrow.setScale({1.f, 1.f});
    backArrow.setPosition(sf::Vector2f(130.f, 130.f));
    backArrow.setRotation(180);

    settings.setPosition(sf::Vector2f(winWidth - 20.f - settings.getGlobalBounds().width - 30.f, 20.f));
}

void LevelSelection::handleEvents(sf::Event& _event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouse->getPosition(*window));

        
        if (backArrow.manageHover(mouse->getPosition(*window)))
        {
         
            backArrow.manage();
            functionIterator = ManagingFunctionsIterator::mainMenu;

        } 
        else if (settings.manageHover(mouse->getPosition(*window)))
        {
            settings.manage();

                
        } 
        else 
        {
            for (int i = 0; i < MapButtonsAmount; i++) 
            {
                mapButtons[i].manageHover(sf::Vector2i(mouse->getPosition(*window)), false);
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
    settings.manageHover(mousePos);
     
}

void LevelSelection::display()
{
    window->draw(backgroundSprite);
    this->window->draw(this->backArrow);
    this->window->draw(this->settings);

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
