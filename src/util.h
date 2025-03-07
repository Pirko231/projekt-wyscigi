#pragma once

#include <SFML/Window/Event.hpp>

namespace util {

// zamiana ze stopni na radiany x * (pi / 180)
float toRadians(float);

// Dzielenie z reszta
// Oblicza liczbe calkowita `n` tak ze:
// `lhs = n * rhs + rem_euclid(lhs, rhs)`
//
// //                               lhs      n    rhs  rem
// div_euclid( 7.0,  4.0) ==  1 //  7.0 ==  4.0 *  1 + 3.0
// div_euclid(-7.0,  4.0) == -2 // -7.0 ==  4.0 * -2 + 1.0
// div_euclid( 7.0, -4.0) == -1 //  7.0 == -4.0 * -1 + 3.0
// div_euclid(-7.0, -4.0) ==  2 // -7.0 == -4.0 *  2 + 1.0
float div_euclid(float, float);

// Oblicza reszte z dzielenia czyli `lhs (mod rhs)`.
// wartosc zwracana `r` spelnia zaleznosc `0.0 <= r <= abs(rhs)`
//
// rem_euclid( 7.0,  4.0) == 3.0
// rem_euclid(-7.0,  4.0) == 1.0
// rem_euclid( 7.0, -4.0) == 3.0
// rem_euclid(-7.0, -4.0) == 1.0
float rem_euclid(float, float);

struct Pressed {
    Pressed();
    void check(sf::Event);

    bool unknown;
    bool a; bool b; bool c;
    bool d; bool e; bool f; bool g;
    bool h; bool i; bool j; bool k;
    bool l; bool m; bool n; bool o;
    bool p; bool q; bool r; bool s;
    bool t; bool u; bool v; bool w;
    bool x; bool y; bool z; bool num0;
    bool num1; bool num2; bool num3; bool num4;
    bool num5; bool num6; bool num7; bool num8;
    bool num9; bool escape; bool lControl; bool lShift;
    bool lAlt; bool lSystem; bool rControl; bool rShift;
    bool rAlt; bool rSystem; bool menu; bool lBracket;
    bool rBracket; bool semicolon; bool comma; bool period;
    bool apostrophe; bool slash; bool backslash; bool grave;
    bool equal; bool hyphen; bool space; bool enter;
    bool backspace; bool tab; bool pageUp; bool pageDown;
    bool end; bool home; bool insert; bool del;
    bool add; bool subtract; bool multiply; bool divide;
    bool left; bool right; bool up; bool down;
    bool numpad0; bool numpad1; bool numpad2; bool numpad3;
    bool numpad4; bool numpad5; bool numpad6; bool numpad7;
    bool numpad8; bool numpad9; bool f1; bool f2;
    bool f3; bool f4; bool f5; bool f6;
    bool f7; bool f8; bool f9; bool f10;
    bool f11; bool f12; bool f13; bool f14;
    bool f15; bool pause; bool keyCount; bool tilde;
    bool dash; bool backSpace; bool backSlash; bool semiColon;
    bool ret; bool quote;
};

}
