#include <cmath>
#include <cstdlib>

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



}
