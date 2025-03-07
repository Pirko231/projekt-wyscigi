#include <algorithm>
#include <cmath>
#include <cstdlib>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <utility>

#include "util.h"

namespace util {

#define PI_OVER_180 0.01745329251994329576
float toRadians(float x)
{
    return x * PI_OVER_180;
}
#undef PI_OVER_180

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

void swap(Vector2& v1, Vector2& v2)
{
    using std::swap;
    swap(v1.x, v2.x);
    swap(v1.y, v2.y);
}

float Vector2::len() const
{
    return sqrtf(x*x + y*y);
}

float Vector2::lenSquared() const
{
    return x*x + y*y;
}

float Vector2::dot(const Vector2& other) const
{
    return x*other.x + y*other.y;
}

float Vector2::cross(const Vector2& other) const
{
    return x*other.y + y*other.x;
}

float Vector2::distance(const Vector2& other) const
{
    float a = x - other.x;
    float b = y - other.y;
    return sqrtf(a*a + b*b);
}
float Vector2::distanceSquared(const Vector2& other) const
{
    float a = x - other.x;
    float b = y - other.y;
    return a*a + b*b;
}

Vector2 Vector2::normalize() const
{
    Vector2 ret = Vector2::zero();
    float length = this->len();
    if (length > 0) {
        float ilength = 1.f/length;
        ret = *this * ilength;
    }
    return ret;
}

Vector2& Vector2::operator=(Vector2 other)
{
    swap(*this, other);

    return *this;
}
Vector2& Vector2::operator+=(const Vector2& other)
{
    x += other.x;
    y += other.y;
    return *this;
}
Vector2& Vector2::operator+=(const float scalar)
{
    x += scalar;
    y += scalar;
    return *this;
}
Vector2& Vector2::operator-=(const Vector2& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}
Vector2& Vector2::operator-=(const float scalar)
{
    x -= scalar;
    y -= scalar;
    return *this;
}
Vector2& Vector2::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
Vector2& Vector2::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}
Vector2 operator+(Vector2 lhs, const Vector2& rhs)
{
    lhs += rhs;
    return lhs;
}
Vector2 operator-(Vector2 lhs, const Vector2& rhs)
{
    lhs -= rhs;
    return lhs;
}
Vector2 operator*(Vector2 lhs, const float rhs)
{
    lhs *= rhs;
    return lhs;
}
Vector2 operator*(float lhs, const Vector2 rhs)
{
    Vector2 ret(rhs.x, rhs.y);
    ret *= lhs;
    return ret;
}
Vector2 operator/(Vector2 lhs, const float rhs)
{
    lhs /= rhs;
    return lhs;
}

Pressed::Pressed() {
    unknown = false;
    a = false; b = false; c = false;
    d = false; e = false; f = false; g = false;
    h = false; i = false; j = false; k = false;
    l = false; m = false; n = false; o = false;
    p = false; q = false; r = false; s = false;
    t = false; u = false; v = false; w = false;
    x = false; y = false; z = false; num0 = false;
    num1 = false; num2 = false; num3 = false; num4 = false;
    num5 = false; num6 = false; num7 = false; num8 = false;
    num9 = false; escape = false; lControl = false; lShift = false;
    lAlt = false; lSystem = false; rControl = false; rShift = false;
    rAlt = false; rSystem = false; menu = false; lBracket = false;
    rBracket = false; semicolon = false; comma = false; period = false;
    apostrophe = false; slash = false; backslash = false; grave = false;
    equal = false; hyphen = false; space = false; enter = false;
    backspace = false; tab = false; pageUp = false; pageDown = false;
    end = false; home = false; insert = false; del = false;
    add = false; subtract = false; multiply = false; divide = false;
    left = false; right = false; up = false; down = false;
    numpad0 = false; numpad1 = false; numpad2 = false; numpad3 = false;
    numpad4 = false; numpad5 = false; numpad6 = false; numpad7 = false;
    numpad8 = false; numpad9 = false; f1 = false; f2 = false;
    f3 = false; f4 = false; f5 = false; f6 = false;
    f7 = false; f8 = false; f9 = false; f10 = false;
    f11 = false; f12 = false; f13 = false; f14 = false;
    f15 = false; pause = false; keyCount = false; tilde = false;
    dash = false; backSpace = false; backSlash = false; semiColon = false;
    ret = false; quote = false;
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
