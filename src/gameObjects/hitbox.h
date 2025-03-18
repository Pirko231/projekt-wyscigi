#pragma once

#include <array>
#include "../util.h"

// prostokat ktory mozna obracac
struct Hitbox {
    float x = 0, y = 0, width = 0, height = 0, rotation = 0;

    Hitbox() : x(0), y(0), width(0), height(0), rotation(0) {}
    Hitbox(float x, float y, float w, float h) : x(x), y(y), width(w), height(h), rotation(0) {}
    Hitbox(float x, float y, float w, float h, float r) : x(x), y(y), width(w), height(h), rotation(r) {}

    std::array<util::Vector2, 4> corners() const;
    bool colliding(Hitbox &other) const;
};
