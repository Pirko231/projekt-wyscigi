#include <cmath>
#include <cstdlib>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "util.h"

namespace util {

float div_euclid(float lhs, float rhs)
{
    float q = std::trunc(lhs / rhs);
    if (std::fmod(lhs, rhs) < 0.0) {
        return (rhs > 0.0) ? q - 1.0 : q + 1.0;
    }
    return q;
}

float rem_euclid(float lhs, float rhs)
{
    float r = std::fmod(lhs, rhs);
    return (r < 0.0) ? r + std::fabs(rhs) : r;
}


void Pressed::check(sf::Event ev)
{
#define ALL()\
    X(unknown, Unknown); X(a, A); X(b, B); X(c, C);\
    X(d, D); X(e, E); X(f, F); X(g, G);\
    X(h, H); X(i, I); X(j, J); X(k, K);\
    X(l, L); X(m, M); X(n, N); X(o, O);\
    X(p, P); X(q, Q); X(r, R); X(s, S);\
    X(t, T); X(u, U); X(v, V); X(w, W);\
    X(x, X); X(y, Y); X(z, Z); X(num0, Num0);\
    X(num1, Num1); X(num2, Num2); X(num3, Num3); X(num4, Num4);\
    X(num5, Num5); X(num6, Num6); X(num7, Num7); X(num8, Num8);\
    X(num9, Num9); X(escape, Escape); X(lControl, LControl); X(lShift, LShift);\
    X(lAlt, LAlt); X(lSystem, LSystem); X(rControl, RControl); X(rShift, RShift);\
    X(rAlt, RAlt); X(rSystem, RSystem); X(menu, Menu); X(lBracket, LBracket);\
    X(rBracket, RBracket); X(semicolon, Semicolon); X(comma, Comma); X(period, Period);\
    X(apostrophe, Apostrophe); X(slash, Slash); X(backslash, Backslash); X(grave, Grave);\
    X(equal, Equal); X(hyphen, Hyphen); X(space, Space); X(enter, Enter);\
    X(backspace, Backspace); X(tab, Tab); X(pageUp, PageUp); X(pageDown, PageDown);\
    X(end, End); X(home, Home); X(insert, Insert); X(del, Delete);\
    X(add, Add); X(subtract, Subtract); X(multiply, Multiply); X(divide, Divide);\
    X(left, Left); X(right, Right); X(up, Up); X(down, Down);\
    X(numpad0, Numpad0); X(numpad1, Numpad1); X(numpad2, Numpad2); X(numpad3, Numpad3);\
    X(numpad4, Numpad4); X(numpad5, Numpad5); X(numpad6, Numpad6); X(numpad7, Numpad7);\
    X(numpad8, Numpad8); X(numpad9, Numpad9); X(f1, F1); X(f2, F2);\
    X(f3, F3); X(f4, F4); X(f5, F5); X(f6, F6);\
    X(f7, F7); X(f8, F8); X(f9, F9); X(f10, F10);\
    X(f11, F11); X(f12, F12); X(f13, F13); X(f14, F14);\
    X(f15, F15); X(pause, Pause); X(keyCount, KeyCount); X(tilde, Tilde);\
    X(dash, Dash); X(backSpace, BackSpace); X(backSlash, BackSlash); X(semiColon, SemiColon);\
    X(ret, Return); X(quote, Quote)
#define X(a, b) if (ev.key.code == sf::Keyboard::b) a = true
    if (ev.type == sf::Event::KeyPressed) {
        ALL();
    }
#undef X
#define X(a, b) if (ev.key.code == sf::Keyboard::b) a = false
    if (ev.type == sf::Event::KeyReleased) {
        ALL();
    }
#undef X
#undef ALL
}

}
