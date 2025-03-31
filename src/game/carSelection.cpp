#include "carSelection.h"

CarSelection::CarSelection(sf::RenderWindow* _window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings)
    : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings}
{
    //raporcik dla szefa
    perf::Raport raport;
    raport.open();
    raport.logMessage("CarSelection");
    raport.addEntry("Wczytywanie tekstury czcionki", lockTexture.loadFromFile("resources/textures/Lock.png"));
    raport.addEntry("Wczytywanie czcionki", font.loadFromFile("resources/fonts/BigFont.ttf"));
    raport.close();
   
    backgroundSprite.setScale(static_cast<float>(_window->getSize().x)/backgroundTexture.getSize().x, static_cast<float>(_window->getSize().y)/backgroundTexture.getSize().y);

    //wczytywanie tekstury klodki
    lockSprite.setTexture(lockTexture);

    //wymiary 
    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.09f;
    float spacing = winWidth * 0.07f;
    float buttonRadius = winWidth * 0.12f;

    constexpr int NUM_CARS = 3;
    constexpr int NUM_ATTRS = 3;
    float totalWidth = NUM_CARS * (2.f * buttonRadius) + (NUM_CARS - 1) * spacing;
    float startX = (winWidth - totalWidth) / 2.f + buttonRadius;
    float centerY = winHeight * 0.5f;

    float arrowOffsetX = winWidth * 0.02f;
    float arrowOffsetY = winHeight * 0.02f;
    float settingsOffsetX = winWidth * 0.02f;
    float settingsOffsetY = winHeight * 0.02f;

    //etykiedy dla kazdego auta
    std::string names[NUM_CARS] = {"Subaru WRX", "Mercedes AMG GT", "Lamborghini Huracan"};
    std::string labelTexts[NUM_ATTRS] = {"Szybkosc", "Zwrotnosc", "TURBO"};

    //klodka
    float desiredLockWidth = buttonRadius * 1.3f;
    float lockScaleFactor = desiredLockWidth / lockTexture.getSize().x;
    lockSprite.setScale(lockScaleFactor, lockScaleFactor);

    for (int i = 0; i < NUM_CARS; i++)
    {
        //ustawienia circlebutton
        sf::Vector2f btnPos(startX + i * (2.f * buttonRadius + spacing), centerY);
        CarCircleBtn[i].setPosition(btnPos);
        CarCircleBtn[i].setRadius(buttonRadius);
        CarCircleBtn[i].setColor(sf::Color::White);
        CarCircleBtn[i].setHoverScaleFactor(1.1f);

        //konfiguracja nazw aut 
        carNames[i].setFont(font);
        carNames[i].setString(names[i]);
        carNames[i].setCharacterSize(24);
        carNames[i].setFillColor(sf::Color::Black);

        carIcons[i].setTexture(settings->getCars()->getTexture(i));
        carIcons[i].setScale(2.f,2.f);

        //przykladowe atrybuty
        carAttributes[i][0] = (settings->getCars()->getStats(i).maxSpeed - 270.f) * 1.2f; // szybkosc
        carAttributes[i][1] = (settings->getCars()->getStats(i).acceleration - 4.f) * 12.f;  // Turbo
        carAttributes[i][2] = (settings->getCars()->getStats(i).rotationSpeed - 4.6f) * 60.f;  // zwrotnosc

        //pozycjonowanie locka
        lockSprite.setPosition(btnPos.x - lockSprite.getGlobalBounds().width/2.f, btnPos.y - lockSprite.getGlobalBounds().height/2.f);

        float margin = buttonRadius * 0.05f;
        float extraOffset = buttonRadius * 0.1f;
        float pbWidth = buttonRadius * 1.5f;
        float pbHeight = buttonRadius * 0.1f;
        float barSectionHeight = pbHeight * 2.f;
        float rectWidth = pbWidth + 2.f * margin;
        float rectHeight = NUM_ATTRS * barSectionHeight + 2.f * margin + pbHeight * 0.2f;

        //rectangle texture na progressbar
        sf::RectangleShape rect;
        rect.setSize({rectWidth, rectHeight});
        rect.setFillColor(sf::Color(200, 200, 200, 150));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.f);
        rect.setPosition(btnPos.x - rectWidth/2.f, btnPos.y + buttonRadius + margin + extraOffset);
        carInfoRects.push_back(rect);

        sf::FloatRect nameRect = carNames[i].getLocalBounds();
        carNames[i].setOrigin(nameRect.left + nameRect.width/2.f, nameRect.top + nameRect.height/2.f);
        carNames[i].setPosition(rect.getPosition().x + rect.getSize().x/2.f, rect.getPosition().y + rect.getSize().y + margin + nameRect.height/2.f);

        carIcons[i].setPosition(CarCircleBtn[i].getPosition().x - carIcons[i].getGlobalBounds().width / 2.f, CarCircleBtn[i].getPosition().y - carIcons[i].getGlobalBounds().height / 2.f);

        float startY = rect.getPosition().y + margin;
        for (int j = 0; j < NUM_ATTRS; j++)
        {
            float posY = startY + j * barSectionHeight + pbHeight * 0.3f;
            sf::Vector2f pbPos(rect.getPosition().x + margin, posY);
            sf::Vector2f pbSize(pbWidth, pbHeight);
            carProgressBars[i][j] = new btn::ProgressBar(pbPos, pbSize, &carAttributes[i][j]);

            attributeLabels[i][j].setFont(font);
            attributeLabels[i][j].setString(labelTexts[j]);
            attributeLabels[i][j].setCharacterSize(18);
            attributeLabels[i][j].setFillColor(sf::Color::Black);
            sf::FloatRect labelRect = attributeLabels[i][j].getLocalBounds();
            float labelX = pbPos.x + pbWidth/2.f - labelRect.width/2.f;
            float labelY = posY - labelRect.height - pbHeight * 0.2f;
            attributeLabels[i][j].setPosition(labelX, labelY);
        }
    }

    //pozycjonowanie strzalki
    backArrow.setPosition(sf::Vector2f(arrowOffsetX, arrowOffsetY));
    //pozycjonowanie ustawien
    settingsBtn.setPosition(sf::Vector2f(winWidth - buttonWidth - settingsOffsetX, settingsOffsetY));
}



void CarSelection::handleEvents(sf::Event &_event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left)
    {
        //sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouse->getPosition(*window));

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
                    
                    int savedMap = this->settings->getStartingData()->mapNumber; 
                    functionIterator = (savedMap == 0) ? ManagingFunctionsIterator::level1 :(savedMap == 1) ? ManagingFunctionsIterator::level2 :ManagingFunctionsIterator::level3;
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
        window->draw(carIcons[i]);
        for (int j = 0; j < NUM_ATTRS; j++)
        {
            window->draw(*carProgressBars[i][j]);
            window->draw(attributeLabels[i][j]);
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
