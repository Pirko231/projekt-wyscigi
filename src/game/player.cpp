

#include "player.h"

//dodalem w klasie na private te zmienne, potem będą zalezne od rodzaju samochodu
//mam pomysl na zrobienie czegos w stylu globalnej struktury ktora bedzie dzialala jak 'garaz'
//i klasy typu level będą pozyczaly tylko wskaznik od tego 'garazu' i uzywala jego aut.
//garaz wczytywalby wtedy tekstury, a komunikacja odbywalaby sie za pomocą
//settings->getStartingData()->zmienna

Player::Player() : Car{}
{
}

void Player::handleEvents(sf::Event& ev)
{
    pressed.check(ev);

    if (pressed.a == pressed.d) {
        controls.steering = Steering::Straight;
    } else if (pressed.a) {
        controls.steering = Steering::Left;
    } else if (pressed.d) {
        controls.steering = Steering::Right;
    }
    if (pressed.w == pressed.s) {
        controls.throttle = Throttle::None;
    } else if (pressed.w) {
        controls.throttle = Throttle::Accelerate;
    } else if (pressed.s) {
        controls.throttle = Throttle::Break;
    }
}
