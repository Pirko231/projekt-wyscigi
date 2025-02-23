#include "mainMenu.h"
#include "raport.h"



MainMenu::MainMenu(sf::RenderWindow *_window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator) : BodyFunction{_window, _mouse, _managingFunctionsIterator}
{
    Raport raport;
    raport.open();
    raport.logMessage("MainMenu");
    raport.addEntry("Wczytywanie czcionki ekran tytulowy" , this->font.loadFromFile("fonts/BigFont.ttf"));
    raport.close();

    std::string buttonNames[buttonAmount] = {"graj", "opcje", "wyjscie"};

    auto [winWidth, winHeight] = _window->getSize();
    float buttonWidth = winWidth * 0.3f;
    float buttonHeight = winHeight * 0.1f; //10% buttonheight
    float spacing = winHeight * 0.15f;  // 15% screenheight
    float startX = (winWidth - buttonWidth) / 2.f;
    float startY = (winHeight - (buttonAmount * (buttonHeight + spacing))) / 2.f;

    for (int i = 0; i < buttonAmount; i++) {
        buttons[i].setFont(font);
        buttons[i].setString(buttonNames[i]);
        buttons[i].setPosition({startX, startY + i * (buttonHeight + spacing)});
        buttons[i].setCharacterSize(static_cast<unsigned int>(buttonHeight * 2.f));
        buttons[i].setFillColor(sf::Color::White);  

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
            buttons[0].reset();
        }
        if (buttons[2].isAnimationFinished()) {
            window->close();
        }   
    }    


void MainMenu::display()
{
    //this->window->draw(this->shape);
    this->window->draw(this->button);

    for(int i = 0; i < buttonAmount; i++) {

       this->window->draw(this->buttons[i]);
    }
}

MainMenu::~MainMenu()
{
}