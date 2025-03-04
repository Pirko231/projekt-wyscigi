

#include "player.h"

//dodalem w klasie na private te zmienne, potem będą zalezne od rodzaju samochodu
//mam pomysl na zrobienie czegos w stylu globalnej struktury ktora bedzie dzialala jak 'garaz'
//i klasy typu level będą pozyczaly tylko wskaznik od tego 'garazu' i uzywala jego aut.
//garaz wczytywalby wtedy tekstury, a komunikacja odbywalaby sie za pomocą
//settings->getStartingData()->zmienna

Player::Player() : Car{}
{
}
