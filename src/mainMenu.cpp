#include "mainMenu.h"
#include "raport.h"

MainMenu::MainMenu(sf::RenderWindow *_window, sf::Mouse* _mouse, ManagingFunctionsIterator& _managingFunctionsIterator) : BodyFunction{_window, _mouse, _managingFunctionsIterator}
{
    Raport raport;
    raport.open();
    raport.logMessage("MainMenu");
    raport.addEntry("Wczytywanie czcionki ekran tytulowy" , this->font.loadFromFile("fonts/BigFont.ttf"));
    raport.close();

    this->button.setFont(font);
    this->button.setString("Gyat");
    this->button.setPosition({50.f, 50.f}); //zdane
    this->button.setCharacterSize(70); //zdane
    this->button.setFillColor(sf::Color::Blue); //zdane
}

void MainMenu::handleEvents(sf::Event& _event)
{
    if (_event.type == sf::Event::MouseButtonPressed)
        if (_event.mouseButton.button == sf::Mouse::Left)
            if(this->button.getHitbox().contains(static_cast<sf::Vector2f>(this->mouse->getPosition(*this->window))))
                this->button.clicked();
        
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
}

MainMenu::~MainMenu()
{
}
