#include "program.h"

int main()
{
    Program program;

    while (program.running())
    {
        //tutaj nie dodajemy juz niczego
        //wszystko ma sie odbywac w tych trzech funkcjach
        program.handleEvents();
        program.update();
        program.display();
    }
}