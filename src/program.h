#include <SFML/Graphics.hpp>

class Program
{
public:
    Program();
    void handleEvents();
    void update();
    void display();
    bool running() const {return this->window->isOpen();}
    ~Program();
private:
    //w tym oknie renderowane beda wszystkie rzeczy
    sf::RenderWindow* window;
};