#include "carSelection.h"

CarSelection::CarSelection(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings, sf::Music* _music)
    : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings, _music}
{
    //screenbackground
    backgroundTexture.loadFromFile("resources/mainMenuBackground.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(_window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(_window->getSize().y) / backgroundTexture.getSize().y
    );

    //wczytywanie tekstury klodki
    lockTexture.loadFromFile("resources/Lock.png");
    lockSprite.setTexture(lockTexture);

    //wymiary 
    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.09f;
    float buttonHeight = winHeight * 0.15f;
    float spacing = winWidth * 0.07f;
    float buttonRadius = winWidth * 0.12f;
    


    constexpr int NUM_CARS = 3;
    constexpr int NUM_ATTRS = 3;
    float totalWidth = NUM_CARS * (2.f * buttonRadius) + (NUM_CARS - 1) * spacing;
    float startX = (winWidth - totalWidth) / 2.f + buttonRadius;
    float centerY = winHeight * 0.5f;

    float arrowOffsetX = winWidth * 0.02f;
    float arrowOffsetY = winHeight * 0.02f;
    float settingsOffsetX = winWidth  * 0.02f;
    float settingsOffsetY = winHeight * 0.02f;

    //wczytanie czcionki
    font.loadFromFile("fonts/BigFont.ttf");
    std::string names[NUM_CARS] = {"Auto 1", "Auto 2", "Auto 3"};

    //klodka
    float desiredLockWidth = buttonRadius * 0.6f;
    float lockScaleFactor = desiredLockWidth / lockTexture.getSize().x;
    lockSprite.setScale(lockScaleFactor, lockScaleFactor);

    for (int i = 0; i < NUM_CARS; i++)
    {
        //ustawienia circlebutton
        sf::Vector2f btnPos(startX + i * (2 * buttonRadius + spacing), centerY);
        CarCircleBtn[i].setPosition(btnPos);
        CarCircleBtn[i].setRadius(buttonRadius);
        CarCircleBtn[i].setColor(sf::Color::White);
        CarCircleBtn[i].setHoverScaleFactor(1.1f);

        //konfiguracja nazw aut 
        carNames[i].setFont(font);
        carNames[i].setString(names[i]);
        carNames[i].setCharacterSize(24);
        carNames[i].setFillColor(sf::Color::Black);

        //PRZYKLAD NA SAM POCZATEK
        carAttributes[i][0] = 100; // szybkosc
        carAttributes[i][1] = 75;  // Turbo
        carAttributes[i][2] = 50;  // zwrotnosc

        //pozycjonowanie locka
        lockSprite.setPosition(
            btnPos.x - lockSprite.getGlobalBounds().width / 2.f,
            btnPos.y - lockSprite.getGlobalBounds().height / 2.f
        );

        // progressbar 
        for (int j = 0; j < NUM_ATTRS; j++)
        {
            float pbWidth  = buttonRadius * 1.5f;
            float pbHeight = buttonRadius * 0.1f;
            sf::Vector2f pbPos;
            pbPos.x = btnPos.x - pbWidth / 2.f;
            pbPos.y = btnPos.y + buttonRadius + (j + 1) * (pbHeight + 5.f);
            sf::Vector2f pbSize(pbWidth, pbHeight);
            carProgressBars[i][j] = new btn::ProgressBar(pbPos, pbSize, &carAttributes[i][j]);
        }

        //rectangle texture na progressbar
        constexpr float margin      = 10.f;
        constexpr float extraOffset = 20.f;
        float pbWidth  = buttonRadius * 1.5f;
        float pbHeight = buttonRadius * 0.1f;
        float rectWidth  = pbWidth + 2 * margin;
        float rectHeight = NUM_ATTRS * (pbHeight + 5.f) + margin;
        sf::RectangleShape rect;
        rect.setSize({rectWidth, rectHeight});
        rect.setFillColor(sf::Color(200, 200, 200, 150)); //przezroczyste
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.f);
        rect.setPosition(btnPos.x - rectWidth / 2.f, btnPos.y + buttonRadius + margin + extraOffset);
        carInfoRects.push_back(rect);

        sf::FloatRect textRect = carNames[i].getLocalBounds();
        carNames[i].setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
        carNames[i].setPosition(
            rect.getPosition().x + rect.getSize().x / 2.f,
            rect.getPosition().y + rect.getSize().y + margin + textRect.height / 2.f
        );
    }

    //pozycja strzalki
    backArrow.setPosition(sf::Vector2f(arrowOffsetX, arrowOffsetY));

    //pozycja ustawien
    settingsBtn.setPosition(sf::Vector2f(winWidth - buttonWidth - settingsOffsetX, settingsOffsetY));
}

void CarSelection::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouse->getPosition(*window));

        for (int i = 0; i < NUM_CARS; i++)
        {
            if (CarCircleBtn[i].manageHover(mouse->getPosition(*window), true))
            {
                bool isUnlocked = (i == 0) ? true : ((i == 1) ? settings->getData()->car2 : settings->getData()->car3);
                if (!isUnlocked)
                {
                   //jesli jest zablokowane to nic sie nie dzieje
                    continue;
                }
                else
                {
                    CarCircleBtn[i].setHoverScaleFactor(1.3f);
                    settings->setStartingData()->carNumber = i;
                    
                    int savedMap = 1; 
                    functionIterator = (savedMap == 1) ? ManagingFunctionsIterator::level1 :(savedMap == 2) ? ManagingFunctionsIterator::level2 :ManagingFunctionsIterator::level3;
                }
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

    for (int i = 0; i < NUM_CARS; i++)
    {
        bool hovered = CarCircleBtn[i].manageHover(mousePos);
        if (!hovered)
        {
            CarCircleBtn[i].setHoverScaleFactor(1.1f);
        }
    }

    backArrow.manageHover(mousePos);
    settingsBtn.manageHover(mousePos);

    if (this->backArrow.manage())
    {
        functionIterator = ManagingFunctionsIterator::levelSelection;
        this->backArrow.reset();
    }
    if (this->settingsBtn.manage())
    {
        *this->BodyFunction::settings = !(*this->BodyFunction::settings);
        this->settingsBtn.reset();
    }
}

void CarSelection::display()
{
    window->draw(backgroundSprite);
    window->draw(backArrow);
    window->draw(settingsBtn);

    for (int i = 0; i < NUM_CARS; i++)
    {
        window->draw(carInfoRects[i]);
        window->draw(CarCircleBtn[i]);
        window->draw(carNames[i]);
        for (int j = 0; j < NUM_ATTRS; j++)
        {
            window->draw(*carProgressBars[i][j]);
        }

        if (i > 0)
        {
            bool isUnlocked = (i == 1) ? settings->getData()->car2 : settings->getData()->car3;
            if (!isUnlocked)
            {
                sf::Vector2f btnPos = CarCircleBtn[i].getPosition();
                lockSprite.setPosition(
                    btnPos.x - lockSprite.getGlobalBounds().width / 2.f,
                    btnPos.y - lockSprite.getGlobalBounds().height / 2.f
                );
                window->draw(lockSprite);
            }
        }
    }
}

CarSelection::~CarSelection()
{
}
