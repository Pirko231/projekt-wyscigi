#include <cmath>

#include "hitbox.h"

// tylko na potrzeby algorytmu
struct Projection {
    float min = 0, max = 0;

    Projection() : min(0), max(0) {}
    Projection(float lhs, float rhs)
    {
        if (lhs <= rhs) {
            min = lhs;
            max = rhs;
        } else {
            min = rhs;
            max = lhs;
        }
    }

    void add(float x) {
        if (x < min) {
            min = x;
        } else if (x > max) {
            max = x;
        }
    }
    bool overlaps(Projection p) {
        return std::max(min, p.min) <= std::min(max, p.max);
    }
};


std::array<util::Vector2, 4> Hitbox::corners() const
{
    float theta = util::radians(rotation);

    return {
        util::Vector2(x, y),
        {x + width*cosf(theta), y + width*sinf(theta)},
        {x - height*sinf(theta), y + height*cosf(theta)},
        {x + width*cosf(theta) - height*sinf(theta), y + width*sinf(theta) + height*cosf(theta)},
    };
}

float rotateX(util::Vector2 v, float theta)
{
    return v.x*cosf(theta) - v.y*sinf(theta);
}

bool projectOver(std::array<util::Vector2, 4> corners, util::Vector2 origin, float theta, float w)
{
    Projection projected(
        rotateX(corners[0] - origin, theta),
        rotateX(corners[1] - origin, theta)
    );
    projected.add(rotateX(corners[2] - origin, theta));
    projected.add(rotateX(corners[3] - origin, theta));

    return projected.overlaps(Projection(0, w));
}

bool Hitbox::colliding(Hitbox &other) const {
    auto corners1 = corners();
    auto corners2 = other.corners();
    float angles[] = {
        util::radians(-rotation),
        util::radians(-90 - rotation),
        util::radians(-other.rotation),
        util::radians(-90 - other.rotation),
    };

    bool ret =
        projectOver(corners2, corners1[0], angles[0], width) &&
        projectOver(corners2, corners1[0], angles[1], height) &&
        projectOver(corners1, corners2[0], angles[2], other.width) &&
        projectOver(corners1, corners2[0], angles[3], other.height);

    return ret;
}
