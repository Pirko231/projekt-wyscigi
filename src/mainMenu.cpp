
#include "mainMenu.h"
#include "raport.h"



MainMenu::MainMenu(sf::RenderWindow* _window, sf::Mouse* _mouse , ManagingFunctionsIterator& _managingFunctionsIterator, Settings* _settings) : BodyFunction{_window, _mouse, _managingFunctionsIterator, _settings}
{
    Raport raport;
    raport.open();
    raport.logMessage("MainMenu");
    raport.addEntry("Wczytywanie czcionki ekran tytulowy" , this->font.loadFromFile("fonts/BigFont.ttf"));
    raport.addEntry("Wczytywanie tła ekran tytulowy", backgroundTexture.loadFromFile("resources/mainMenuBackground.jpg"));
    raport.addEntry("Wczytywanie muzyki na ekran tytulowy", menuMusic.openFromFile("sounds/MainMenuMusic.wav"));
    raport.close();

    std::string buttonNames[buttonAmount] = {"graj", "opcje", "wyjscie"};

    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.3f;
    float buttonHeight = winHeight * 0.1f; //10% buttonheight
    float spacing = winHeight * 0.02f;  // 8% screenheight
    float startX = (winWidth - buttonWidth) / 1.7f;
    float startY = (winHeight - (buttonAmount * (buttonHeight + spacing))) / 2.f;

    for (int i = 0; i < buttonAmount; i++) {
        buttons[i].setFont(font);
        buttons[i].setString(buttonNames[i]);
        buttons[i].setPosition({startX, startY + i * (buttonHeight + spacing)});
        buttons[i].setCharacterSize(static_cast<unsigned int>(buttonHeight * 1.f));
        buttons[i].setFillColor(sf::Color::Black);  

    }
    
    //screen background
    backgroundTexture.loadFromFile("resources/mainMenuBackground.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(_window->getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(_window->getSize().y) / backgroundTexture.getSize().y
    );

    //overlay for buttons (alfa)
    overlay.setSize(sf::Vector2f(buttonWidth * 1.1f, buttonHeight * 3.5 + spacing * 2));
    overlay.setPosition(
    startX - (buttonWidth * 0.3f),
    startY  
    );
    overlay.setFillColor(sf::Color(255, 255, 255, 150));

    //Soundtrack loading
    //menuMusic.openFromFile("sounds/MainMenuMusic.wav");
    menuMusic.setVolume(10.f);
    menuMusic.setLoop(true);
    
}

//Soundtrack
void MainMenu::playMenuMusic() {
    if (menuMusic.getStatus() != sf::Music::Playing) {
        menuMusic.play();
    }
}

void MainMenu::handleEvents(sf::Event& _event)
{
    if (_event.type == sf::Event::MouseButtonPressed && _event.mouseButton.button == sf::Mouse::Left) {
        for (int i = 0; i < buttonAmount; i++) {
            if (buttons[i].getHitbox().contains(static_cast<sf::Vector2f>(mouse->getPosition(*window)))) {
                buttons[i].startClickAnimation();
            }
        }
    }
}


void MainMenu::update()
    {
        playMenuMusic();

        for (int i = 0; i < buttonAmount; i++) {
            if (buttons[i].isAnimated()) {
                this->buttons[i].clicked(); 

            }   
            if (buttons[i].getHitbox().contains(static_cast<sf::Vector2f>(mouse->getPosition(*window)))) {
                buttons[i].howered();
            } else {
                buttons[i].unHowered();
            }
        }
    
        if (buttons[0].isAnimationFinished()) {
            functionIterator = ManagingFunctionsIterator::levelSelection;
            for (int i = 0; i < buttonAmount; i++) {
                buttons[i].reset();
            }

        }
        if (buttons[2].isAnimationFinished()) {
            window->close();
        }   
    }    


void MainMenu::display()
{
    //this->window->draw(this->shape);
    window->draw(backgroundSprite);
    window->draw(overlay);

    for(int i = 0; i < buttonAmount; i++) {

       this->window->draw(this->buttons[i]);
    }
}

MainMenu::~MainMenu()
{
}
